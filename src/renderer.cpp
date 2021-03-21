#include "renderer.h"

#include <limits>

Renderer::Renderer(Image& m,const float f, const Image& e)
    :image(m), fov(f), env(e), ray_trace_times(4){}

Renderer::~Renderer() {}

vec3f  Renderer::reflect(const vec3f& I, const vec3f& N) {
    return I - 2 * N * (N * I);
}

vec3f Renderer::refract(const vec3f& I, const vec3f& N, const float& refractive_index) {
    // implement refer: https://en.wikipedia.org/wiki/Snell%27s_law vector form
    float cos_theta_1 = -(I * N);
    float n1 = 1;
    float n2 = refractive_index;
    vec3f n = N;
    if(cos_theta_1 < 0) { // if cos(theta_1) is negative, it indicates the ray is in the object inner, we will exchange params.
        cos_theta_1 = -cos_theta_1;
        std::swap(n1, n2);
        n = -n;
    }

    float k = 1 - (n1 / n2) * (n1 / n2) * (1 - cos_theta_1 * cos_theta_1);
    float cos_theat_2 = std::sqrt(k);
    return k < 0 ? vec3f(1, 0, 0) : I * (n1 / n2) + ((n1 / n2) * cos_theta_1 - cos_theat_2) * n; // k less zero return a vector(1, 0, 0)  to avoid normalized() errors, it is not any physical meaning.
}


vec3f Renderer::cast_ray(const vec3f& orig, const vec3f& d, const std::vector<std::shared_ptr<Mesh>>& scene, const std::vector<Light>& lights, std::size_t depth) {
    vec3f hitPoint, normal;
    Material material;
    if(depth > ray_trace_times || !scene_intersect(orig, d, scene, hitPoint, normal, material)) {
        int a = std::max(0, std::min(env.getWidth() -1, static_cast<int>((atan2(d.z, d.x) / (2 * M_PI) + .5)* env.getWidth()))); // TODO understand why
        int b = std::max(0, std::min(env.getHeight() -1, static_cast<int>(acos(d.y) / M_PI * env.getHeight()))); // TODO understand why
        return env.getPixelColor(a, b); // background color
    }

    vec3f reflect_ray = reflect(d, normal).normalize();
    vec3f reflect_point = reflect_ray * normal > 0 ? hitPoint + normal * 1e-3 : hitPoint - normal * 1e-3; // avoid intersect with itselt, let it is above or down a little.
    vec3f reflect_color = cast_ray(reflect_point, reflect_ray, scene, lights, depth + 1);

    vec3f refract_ray = refract(d, normal, material.getRefractiveIndex()).normalize();
    vec3f refract_point = refract_ray * normal < 0 ? hitPoint - normal * 1e-3  : hitPoint + normal * 1e-3;
    vec3f refract_color = cast_ray(refract_point, refract_ray, scene, lights, depth + 1);
    
    float diffuse_intensity = 0;
    float specular_intensity = 0;

    for(const auto& light: lights) {
        vec3f light_dir = (light.getPoint() - hitPoint).normalize();
        double distance = (light.getPoint() - hitPoint).norm();
        vec3f shadow_orig = light_dir * normal < 0 ? hitPoint - normal * 1e-3 : hitPoint + normal * 1e-3; // because the point lies on the surface, it's will make the line from this to lightDir don't intersect with itself.
        vec3f shadow_hit, shadow_normal;
        Material tempMaterial;
        if(scene_intersect(shadow_orig, light_dir, scene, shadow_hit, shadow_normal, tempMaterial) && (shadow_orig - shadow_hit).norm() < distance) // if there another intersect point with others object, we will think the ray is sheltered, skit it!
            continue;
        diffuse_intensity += light.getIntensity() * std::max(0.0f, normal * light_dir);
        specular_intensity += light.getIntensity() * powf(std::max(0.0f, reflect(light_dir, normal) * d), material.getSpecularExponent());
    }

    return material.getDiffuseColor() * diffuse_intensity * material.getAlbedo().x +
           vec3f(1, 1, 1) * specular_intensity * material.getAlbedo().y +
           reflect_color * material.getAlbedo().z +
           refract_color * material.getAlbedo().w;
    
}

void Renderer::render(const std::vector<std::shared_ptr<Mesh>>& scene, const std::vector<Light>& lights) {
    #pragma omp parallel for
    for(size_t x = 0; x < image.getWidth(); x++) {
        for(size_t y = 0; y < image.getHeight(); y++) {
            float dx = (2 * (x  + 0.5)/(float)image.getWidth() - 1) * std::tan(fov / 2.0f) * image.getRatio();
            float dy = -(2 * (y + 0.5)/(float)image.getHeight() - 1) * std::tan(fov / 2.0f);
            vec3f d = vec3f(dx, dy, -1).normalize();
            image.set(x, y, cast_ray(vec3f(0,0,0), d, scene, lights, 0));
        }
    }
}

bool Renderer::scene_intersect(const vec3f& orig, const vec3f& d, const std::vector<std::shared_ptr<Mesh>>& scene, vec3f& hit, vec3f& normal, Material& material) {
    float mesh_t = std::numeric_limits<float>::max();
    for(const auto& mesh: scene) {
        auto rs = mesh->rayIntersect(orig, d);
        if(rs.has_value() && rs.value().t < mesh_t) {
            mesh_t = rs.value().t;
            hit = rs.value().hitPosition;
            normal = rs.value().normal;
            material = rs.value().material;
        }
    }

    float checkerboard_t = std::numeric_limits<float>::max();
    if(std::fabs(d.y) > 1e-3) {
        float cb_t= -(orig.y + 4) / d.y; // the checkerboard plane has equation y = -4, cb_t is ray intersect with the checkerboard plane
        vec3f cb_hit_point = orig + cb_t * d; // the point the ray intersect with checkerboard plane
        if(cb_t > 0 && std::fabs(cb_hit_point.x) < 10 && 
            cb_hit_point.z < -10 && cb_hit_point.z > -30 && cb_t < mesh_t) {
                checkerboard_t = cb_t;
                hit = cb_hit_point;
                normal = vec3f(0, 1, 0);
                material.setDiffuse((int(.5 * hit.x + 1000) + int(.5 * hit.z)) & 1 ? vec3f(.3, .3, .3) : vec3f(.3, .2, .1)); // TODO understand why
            }
    } 

    return std::min(mesh_t, checkerboard_t) < 1000;
}

void Renderer::output(const std::string& filepath) {
    image.write(filepath);
}

void Renderer::setRayTraceTimes(const int& t) {
    ray_trace_times = t;
}