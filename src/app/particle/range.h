#pragma once

#include <glm/vec2.hpp>

namespace ParticleOfLife {

    class Range {
        public:
            static void wrap(glm::dvec2& /*v*/);
            static double wrap(double /*v*/);

    };
}