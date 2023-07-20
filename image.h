#include <glm/glm.hpp>

#ifndef __IMAGE_H__
#define __IMAGE_H__

class Image {
    unsigned int m_width;
    unsigned int m_height;
    
    glm::dvec3 * m_pixels;

public:
    Image(unsigned int width, unsigned int height);
    ~Image();

    unsigned int get_width();
    unsigned int get_height();

    void colour_pixel(glm::vec3 colour, unsigned int x, unsigned int y);

    void print();
};

#endif
