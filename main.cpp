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
    Material      ivory(vec2f(0.6,  0.3), vec3f(0.4, 0.4, 0.3),   50.);
    Material red_rubber(vec2f(0.9,  0.1), vec3f(0.3, 0.1, 0.1),   10.);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(vec3f(-3,    0,   -16), 2, ivory));
    spheres.push_back(Sphere(vec3f(-1.0, -1.5, -12), 2, red_rubber));
    spheres.push_back(Sphere(vec3f( 1.5, -0.5, -18), 3, red_rubber));
    spheres.push_back(Sphere(vec3f( 7,    5,   -18), 4, ivory));

    std::vector<Light> lights;
    lights.push_back(Light(vec3f( 30, 50, 25), 1.8));
    lights.push_back(Light(vec3f( 30, -20, 30), 1.7));
    r.render(spheres, lights);
    r.output(result_path);
}
