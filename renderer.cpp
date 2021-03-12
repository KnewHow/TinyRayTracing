#include "renderer.h"

#include <limits>

Renderer::Renderer(Image& m,const float f)
    :image(m), fov(f){}

Renderer::~Renderer() {}

vec3f  Renderer::reflect(const vec3f& I, const vec3f& N) {
    return I - 2 * N * (N * I);
}

vec3f Renderer::cast_ray(const vec3f& orig, const vec3f& d, const std::vector<Sphere>& scene, const std::vector<Light>& lights) {
    
    vec3f hitPoint, normal;
    Material material;
    if(scene_intersect(orig, d, scene, hitPoint, normal, material)) {
        float diffuse_intensity = 0;
        float specular_intensity = 0;
        for(const auto& light: lights) {
            vec3f light_dir = (light.getPoint() - hitPoint).normalize();
            diffuse_intensity += light.getIntensity() * std::max(0.0f, normal * light_dir);
            specular_intensity += powf(std::max(0.0f, reflect(light_dir, normal) * d), material.getSpecularExponent()) * light.getIntensity();
        }
        return material.getDiffuseColor() * (diffuse_intensity + specular_intensity);
    }
    return vec3f(0.2, 0.7, 0.8); // background color
}

void Renderer::render(const std::vector<Sphere>& scene, const std::vector<Light>& lights) {
    for(size_t x = 0; x < image.getWidth(); x++) {
        for(size_t y = 0; y < image.getHeight(); y++) {
            float dx = (2 * (x  + 0.5)/(float)image.getWidth() - 1) * std::tan(fov / 2.0f) * image.getRatio();
            float dy = -(2 * (y + 0.5)/(float)image.getHeight() - 1) * std::tan(fov / 2.0f);
            vec3f d = vec3f(dx, dy, -1).normalize();
            image.set(x, y, cast_ray(vec3f(0,0,0), d, scene, lights));
        }
    }
}

bool Renderer::scene_intersect(const vec3f& orig, const vec3f& d, const std::vector<Sphere>& spheres, vec3f& hit, vec3f& normal, Material& material) {
    bool isIntersect = false;
    float t = std::numeric_limits<float>::max();
    for(const Sphere& sphere: spheres) {
        float t0;
        if(sphere.rayIntersect(orig, d, t0) && t0 < t) {
            isIntersect = true;
            t = t0;
            hit = orig + t * d;
            normal = (hit - sphere.getCenter()).normalize();
            material = sphere.getMaterial();
        }
    }
    return isIntersect;
}

void Renderer::output(const std::string& filepath) {
    image.write(filepath);
}