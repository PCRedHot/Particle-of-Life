#include <glm/vec2.hpp>
#include <cmath>

#include "range.h"

using namespace ParticleOfLife;

void Range::wrap(glm::dvec2& v) {
    v.x = wrap(v.x);
    v.y = wrap(v.y);
}

double Range::wrap(double v) {
    return std::fmod(v + 1, 2) - 1;
};