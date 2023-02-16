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

void Range::clamp(glm::dvec2& v) {
    v.x = clamp(v.x);
    v.y = clamp(v.y);
}

double Range::clamp(double v) {
    if (v < -1) {
        return -1;
    } else if (v > 1) {
        return 1;
    }
    return v;
};