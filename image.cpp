#include "image.h"

#include <fstream>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image_write.h"

Image::Image(int w, int h)
    :width(w), height(h), fragment_buffer(w * h, vec3f(0,0,0))
{
    
}

Image::~Image()
{

}

void Image::write(const std::string& filepath) {
    std::vector<unsigned char> pixmap(width*height*3);
    for (size_t i = 0; i < height*width; ++i) {
        vec3f &c = fragment_buffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1./max);
        for (size_t j = 0; j<3; j++) {
            pixmap[i*3+j] = (unsigned char)(255 * std::max(0.f, std::min(1.f, fragment_buffer[i][j])));
        }
    }
    stbi_write_jpg(filepath.c_str(), width, height, 3, pixmap.data(), 100);
}

void Image::set(int x, int y, const vec3f& rgb) {
    int idx = x + y * width;
    fragment_buffer[idx] = rgb;
}