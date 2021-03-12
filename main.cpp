#include <iostream>

#include "image.h"
#include "renderer.h"
#include "global.h"

int main(int, char**) {
    int width = 1366;
    int height = 768;
    Image image(width, height);
    std::string result_path = "./result.ppm";
    Renderer r(image, MY_PI/2);
    Material      ivory(vec3f(0.4, 0.4, 0.3));
    Material red_rubber(vec3f(0.3, 0.1, 0.1));

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(vec3f(-3,    0,   -16), 2, ivory));
    spheres.push_back(Sphere(vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(vec3f( 7,    5,   -18), 4, ivory));

    std::vector<Light> lights;
    lights.push_back(Light(vec3f(-20, 20,  20), 1.5));
    r.render(spheres, lights);
    r.output(result_path);
}
