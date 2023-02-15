#pragma once

#include <glm/vec2.hpp>

namespace ParticleOfLife {
    struct Particle {
        public:
            glm::dvec2 position = glm::dvec2(0.0f);
            glm::dvec2 velocity = glm::dvec2(0.0f);
            int type = 0;

            Particle();
            Particle(int /*numType*/);
    };
}
