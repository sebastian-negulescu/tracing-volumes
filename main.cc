#include <iostream>
#include <glm/glm.hpp>

#include "image.h"
#include "sphere.h"
#include "trace.h"
#include "beer.h"
#include "scatter.h"
#include "light.h"
#include "phase.h"
#include "perlin.h"

int main( int argc, char* argv[] ) {
    unsigned int width = std::stoi(argv[1]);
    unsigned int height = std::stoi(argv[2]);

    Image image(width, height);

    Light light(glm::vec4(0.0f, -300.0f, -10.0f, 1.0f), glm::vec3(100.0, 50.0, 0.0));

    Beer beer_material(glm::vec3(1.0, 1.0, 1.0), 0.5);
    Phase hg_phase(0.8);
    Perlin perlin;
    Scatter scatter_material(hg_phase, perlin, 0.5, 0.5, 0.25);

    Sphere scene(glm::vec4(0.0f, 0.0f, -10.0f, 1.0f), 7.0f, scatter_material);

    Trace raytracer(image, scene, light);
    raytracer.cast_rays();

    image.print();
}
