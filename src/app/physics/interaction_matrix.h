#pragma once

#include <string>

#include "accelerator.h"

namespace ParticleOfLife {
    namespace Physics {
        class InteractionMatrix {
            public:
                InteractionMatrix();
                InteractionMatrix(int /*size*/);
                ~InteractionMatrix();

                int size();
                float getValue(int /*i*/, int /*j*/);
                float* getValuePointer(int /*i*/, int /*j*/);
                AccelerateType getType(int /*i*/, int /*j*/);

                void setValue(int /*i*/, int /*j*/, double /*v*/);
                void setType(int /*i*/, int /*j*/, AccelerateType /*v*/);
                void resetValue();
                void resetType();
                void randomizeValue(double /*maxMag*/);

                void setSymmetric(bool /*v*/);
                bool* getSymmetricControlPointer();

                void addType();
                void removeType(int /*i*/);

                InteractionMatrix deepCopy();
                // InteractionMatrix extract(int* /*indices*/);

                bool operator==(InteractionMatrix /*o*/);
                bool operator!=(InteractionMatrix /*o*/);
            
            private:
                int n; // size
                bool isSymmetric = false;

                float *values;
                AccelerateType *types;
        };
    }
}