#include "image.h"

#include <fstream>
#include <iostream>

Image::Image(int w, int h)
    :width(w), height(h), fragment_buffer(w * h, vec3f(0,0,0))
{
    
}

Image::~Image()
{

}

void Image::write(const std::string& filepath) {
    std::ofstream ofs;
    ofs.open(filepath);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for(size_t i = 0; i < width * height; i++) {
        for(size_t j = 0; j < 3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, fragment_buffer[i][j])));
        }
    }
    ofs.close();
}

void Image::set(int x, int y, const vec3f& rgb) {
    int idx = x + y * width;
    fragment_buffer[idx] = rgb;
}