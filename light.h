#include <glm/glm.hpp>

#ifndef __LIGHT_H__
#define __LIGHT_H__

class Light {
    glm::vec4 m_position;
    glm::dvec3 m_colour;

public:
    Light(glm::vec4 position, glm::dvec3 colour);

    glm::vec4 get_position();
    glm::dvec3 get_colour();
};

#endif
