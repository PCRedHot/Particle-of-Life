#pragma once

#include "accelerator.h"

namespace ParticleOfLife {
    namespace Physics {
        class InteractionMatrix {
            public:
                InteractionMatrix();
                InteractionMatrix(int /*size*/);
                ~InteractionMatrix();

                int size();
                double getValue(int /*i*/, int /*j*/);
                AccelerateType getType(int /*i*/, int /*j*/);

                void setValue(int /*i*/, int /*j*/, double /*v*/);
                void setType(int /*i*/, int /*j*/, AccelerateType /*v*/);
                void randomize(double /*maxMag*/);

                InteractionMatrix deepCopy();
                InteractionMatrix extract(int* /*indices*/);

                bool operator==(InteractionMatrix /*o*/);
                bool operator!=(InteractionMatrix /*o*/);
            
            private:
                int n; // size

                double **values;
                AccelerateType **types;
        };
    }
}