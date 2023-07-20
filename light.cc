#include "light.h"

Light::Light(glm::vec4 position, glm::vec3 colour) : m_position(position), m_colour(colour) {}

glm::vec4 Light::get_position() {
    return m_position;
}

glm::vec3 Light::get_colour() {
    return m_colour;
}
