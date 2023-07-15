#include <iostream>
#include <glm/glm.hpp>

#include "image.h"
#include "sphere.h"
#include "trace.h"

int main( int argc, char* argv[] ) {
    unsigned int width = std::stoi(argv[1]);
    unsigned int height = std::stoi(argv[2]);

    Image image(width, height);

    glm::vec4 position(0.0f, 0.0f, -3.0f, 0.0f);
    float radius = 2.0f;
    Sphere scene(position, radius);

    Trace raytracer(image, scene);
    raytracer.cast_rays();

    image.print();

    // std::cout << "hello" << std::endl;
}
