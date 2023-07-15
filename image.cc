#include <iostream>

#include "image.h"

Image::Image(unsigned int width, unsigned int height) : m_width(width), m_height(height) {
    m_pixels = new glm::dvec3[m_width * m_height];
}

Image::~Image() {
    delete[] m_pixels;
}

unsigned int Image::get_width() {
    return m_width;
}

unsigned int Image::get_height() {
    return m_height;
}

void Image::colour_pixel(glm::dvec3 colour, unsigned int x, unsigned int y) {
    m_pixels[y * m_width + x] = colour; 
}

void Image::print() {
    std::cout << "P3\n" << m_width << ' ' << m_height << "\n255\n";
    for (unsigned int y = m_height; y > 0; --y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            glm::dvec3 pixel = m_pixels[(y - 1) * m_width + x];
            unsigned int r = (unsigned int) (255.999 * glm::clamp(pixel.r, 0.0, 1.0));
            unsigned int g = (unsigned int) (255.999 * glm::clamp(pixel.g, 0.0, 1.0));
            unsigned int b = (unsigned int) (255.999 * glm::clamp(pixel.b, 0.0, 1.0));
            std::cout << r << ' ' << g << ' ' << b << '\n';
        }
    }
}
