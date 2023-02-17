#pragma once

#include <glm/vec2.hpp>
#include <map>

namespace ParticleOfLife {
    namespace Physics {
        // class Accelerator {
        //     public:
        //         virtual static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class Accelerator {
        //     public:
        //        virtual glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class UniformAccelerator : public Accelerator {
        //     public:
        //         glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class InverseAccelerator : public Accelerator {
        //     public:
        //         glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class InverseSquareAccelerator : public Accelerator {
        //     public:
        //         glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class InverseCubeAccelerator : public Accelerator {
        //     public:
        //         glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        // class Rotate90Accelerator : public Accelerator {
        //     public:
        //         glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        // };

        class UniformAccelerator {
            public:
                static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseAccelerator {
            public:
                static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseSquareAccelerator {
            public:
                static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class InverseCubeAccelerator {
            public:
                static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        class Rotate90Accelerator {
            public:
                static glm::dvec2 accelerate(double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        };

        enum class AccelerateType : int {
            UNIFORM, INVERSE, INVERSE_SQUARE, INVERSE_CUBE, ROTATE_90, Count
        };

        // extern std::map<AccelerateType, Accelerator*> acceleratorTypeMap;

        glm::dvec2 accelerate(AccelerateType /*type*/, double /*typeInteraction*/, glm::dvec2 /*relativePos*/);
        
        std::string getAccelerateTypeString(AccelerateType /*type*/);
        std::string getAccelerateTypeDescription();
    }
}
