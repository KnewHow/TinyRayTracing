#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "image.h"
#include "renderer.h"
#include "mesh/mesh.h"
#include "mesh/sphere.h"
#include "mesh/model.h"
#include "global.h"
#include "accelerator/bvh.h"



int main(int, char**) {
    int width = 1366;
    int height = 768;
    Image image(width, height);
    std::string result_path = "../out.jpg";
    
    // environment picture loader
    std::string env_path = "../res/envmap.jpg";
    int env_width;
    int env_height;
    int env_comp;
    unsigned char *env_data = stbi_load(env_path.c_str(), &env_width, &env_height, &env_comp, 0);
    Image envImage(env_width, env_height);
    std::cout << "env width: " << env_width << ", env height: " << env_height << ", env_comps: " << env_comp << std::endl;
    #pragma omp parallel for
    for(int x = 0; x < env_width; x++) {
        for(int y = 0; y < env_height; y++) {
            vec3f rgb = vec3f(0,0,0);
            for(int i = 0; i < 3; i++) {
                rgb[i] = (env_data[(x + y * env_width) * 3 + i]);
            }
            rgb = rgb / 255.0f;
            envImage.set(x, y, rgb);
        }
    }
    stbi_image_free(env_data);
    
    Material      ivory(vec4f(0.6,  0.3, 0.1, 0.0), vec3f(0.4, 0.4, 0.3),   50.0f, 1.0f);
    Material      glass(vec4f(0.0,  0.5, 0.1, 0.8), vec3f(0.6, 0.7, 0.8),  125.0, 1.5f);
    Material red_rubber(vec4f(0.9,  0.1, 0.0, 0.0), vec3f(0.3, 0.1, 0.1),   10.0f, 1.0f);
    Material     mirror(vec4f(0.0, 10.0, 0.8, 0.0), vec3f(1.0, 1.0, 1.0), 1425.0f, 1.0f);

    std::vector<std::shared_ptr<Mesh>> scene;
    scene.push_back(std::make_shared<Sphere>(vec3f(-3,    0,   -16), 2,      ivory));
    scene.push_back(std::make_shared<Sphere>(vec3f(-1.0, -1.5, -12), 2,      glass));
    scene.push_back(std::make_shared<Sphere>(vec3f( 1.5, -0.5, -18), 3, red_rubber));
    scene.push_back(std::make_shared<Sphere>(vec3f( 7,    5,   -20), 4,     mirror));
    scene.push_back(std::make_shared<Model>("../res/duck.obj", mirror));

    std::vector<Light> lights;
    lights.push_back(Light(vec3f(-20, 20,  20), 1.5));
    lights.push_back(Light(vec3f( 30, 50, -25), 1.8));
    lights.push_back(Light(vec3f( 30, 20,  30), 1.7));
    
    Renderer r(image, MY_PI/3, envImage);
    time_t begin, end;
    begin = time(nullptr);
    r.render(scene, lights);
    end = time(nullptr);
    std::cout << "rendering took: " << (end - begin) << " seconds." << std::endl;
    r.output(result_path);
    
    image.write(result_path);
    return 0;
}
