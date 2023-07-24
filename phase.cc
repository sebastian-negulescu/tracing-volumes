#include <math.h>
#include "phase.h"

Phase::Phase(float g) : m_g(g) {}

float Phase::evaluate(glm::vec4 & light, glm::vec4 & eye) {
    return 1.0f / (4.0f * M_PI) * (1.0f - m_g * m_g) / glm::pow(1.0f + m_g * m_g - 2.0f * m_g * glm::dot(eye, light), 3.0f / 2.0f);
}
