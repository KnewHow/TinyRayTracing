#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <vector>
#include <string>

#include "geometry.h"

class Image
{
private:
   int width;
   int height;
   std::vector<vec3f> fragment_buffer;
public:
    Image(int w, int h);
    ~Image();
    void write(const std::string& filepath);
    void set(int x, int y, const vec3f& rgb);
    inline int getWidth() const{ return width; }
    inline int getHeight() const { return height; }
    inline float getRatio() const { return (float)width/(float)height; }
    inline const std::vector<vec3f>& getBuffer() const { return fragment_buffer; }
    inline const vec3f& getPixelColor(int x, int y) const { return fragment_buffer[x + y * width]; }
};

#endif
