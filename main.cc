#include <iostream>
#include <glm/glm.hpp>

#include "image.h"
#include "sphere.h"
#include "trace.h"
#include "beer.h"
#include "scatter.h"
#include "light.h"

int main( int argc, char* argv[] ) {
    unsigned int width = std::stoi(argv[1]);
    unsigned int height = std::stoi(argv[2]);

    Image image(width, height);

    glm::vec4 position(0.0f, 0.0f, -20.0f, 1.0f);
    float radius = 10.0f;

    Light light(glm::vec4(0.0f, 20.0f, -20.0f, 1.0f), glm::dvec3(1.0, 0.5, 0.0));

    Beer beer_material(glm::dvec3(1.0, 1.0, 1.0), 0.5);
    Scatter scatter_material(0.01, 0.1);

    Sphere scene(position, radius, scatter_material);

    Trace raytracer(image, scene, light);
    raytracer.cast_rays();

    image.print();

    // std::cout << "hello" << std::endl;
}
