#include "ray.h"

Ray::Ray(glm::vec4 origin, glm::vec4 direction) : m_origin(origin), m_direction(direction) {}

glm::vec4 Ray::get_origin() {
    return m_origin;
}

glm::vec4 Ray::get_direction() {
    return m_direction;
}
