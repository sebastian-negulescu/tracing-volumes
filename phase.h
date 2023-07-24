#include <glm/glm.hpp>

#ifndef __PHASE_H__
#define __PHASE_H__

class Phase {
    float m_g;

public:
    Phase(float g);
    float evaluate(glm::vec4 & light, glm::vec4 & eye);
};

#endif
