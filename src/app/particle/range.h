#pragma once

#include <glm/vec2.hpp>

namespace ParticleOfLife {

    static class Range {
        public:
            static void wrap(glm::dvec2& /*v*/);
            static double wrap(double /*v*/);

    }
}