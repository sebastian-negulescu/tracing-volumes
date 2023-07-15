#include <glm/glm.hpp>

#ifndef __RAY_H__
#define __RAY_H__

class Ray {
    glm::vec4 m_origin;
    glm::vec4 m_direction;

public:
    Ray(glm::vec4 origin, glm::vec4 direction);

    glm::vec4 get_origin();
    glm::vec4 get_direction();
};

#endif
