#include <iostream>

#include "image.h"

int main(int, char**) {
    int width = 800;
    int height = 800;
    image image(width, height);
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            image.set(i, j, vec3f((float)i/width, (float)j/height, 0));
        }
    }
    image.write("./result.ppm");
}
