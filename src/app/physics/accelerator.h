#pragma once

#include <glm/vec2.hpp>
#include <map>

namespace ParticleOfLife {
    namespace Physics {
        // class Accelerator {
        //     public:
        //         virtual static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        class Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class UniformAccelerator : public Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseAccelerator : public Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseSquareAccelerator : public Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseCubeAccelerator : public Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class Rotate90Accelerator : public Accelerator {
            public:
                glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        enum class AccelerateType {
            UNIFORM, INVERSE, INVERSE_SQUARE, INVERSE_CUBE, ROTATE_90
        };

        extern std::map<AccelerateType, Accelerator> acceleratorTypeMap;

        glm::dvec2 accelerate(AccelerateType /*type*/, double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
    }
}
