#pragma once

// #include <memory>

namespace ParticleOfLife {
    namespace Physics {
        class InteractionMatrix {
            public:
                InteractionMatrix();
                InteractionMatrix(int /*size*/);
                ~InteractionMatrix();

                int size();
                double get(int /*i*/, int /*j*/);
                void set(int /*i*/, int /*j*/, double /*v*/);
                void randomize(double /*maxMag*/);

                InteractionMatrix deepCopy();
                InteractionMatrix extract(int* /*indices*/);

                bool operator==(InteractionMatrix /*o*/);
                bool operator!=(InteractionMatrix /*o*/);
            
            private:
                int n; // size

                double **values;
        };
    }
}