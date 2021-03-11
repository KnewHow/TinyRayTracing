#include <vector>
#include <string>

#include "geometry.h"


class image
{
private:
   int width;
   int height;
   std::vector<vec3f> fragment_buffer;
public:
    image(int w, int h);
    ~image();
    void write(const std::string& filepath);
    void set(int x, int y, const vec3f& rgb);
};
