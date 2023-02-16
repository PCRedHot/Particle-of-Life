#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "particle.h"
#include "interaction_matrix.h"

namespace ParticleOfLife {
    namespace Physics {
        class PhysicsSetting {
            public:
                PhysicsSetting();
                ~PhysicsSetting();

                InteractionMatrix interactionMatrix = InteractionMatrix(TYPE_SIZE);
                double rMax = 0.04;
                double velocityHalfLife = 0.043;
                double forceScale = 1.0;
                        
                bool wrap = true;       // Interaction at boarder and other side
                
                PhysicsSetting deepCopy();
                bool operator==(PhysicsSetting /*o*/);
                bool operator!=(PhysicsSetting /*o*/);

            private:
                static const int TYPE_SIZE = 7;
        };

        class PhysicsEngine {
            public:
                PhysicsEngine();
                ~PhysicsEngine();

                PhysicsSetting setting; // Setting of the physics rules
                std::vector<Particle> particles;    // List of particles


                int getTypeCount();
                void setParticleCount(int /*num*/);
                

                void simulate(double /*dt*/);
                

            private:
                // Grid Buffers
                std::vector<int> grids;
                const glm::ivec2 gridNeighborhood[9] {
                    glm::ivec2(-1, -1),
                    glm::ivec2( 0, -1),
                    glm::ivec2( 1, -1),
                    glm::ivec2(-1,  0),
                    glm::ivec2( 0,  0),
                    glm::ivec2( 1,  0),
                    glm::ivec2(-1,  1),
                    glm::ivec2( 0,  1),
                    glm::ivec2( 1,  1),
                };
                std::vector<Particle> particlesBuffer;

                // Simulation Grid Layout
                int nx, ny;
                double gridSize = 0.13;
                double prevGridSize = 0.13;

                void calculateNxNy();
                void generateInteractionMatrix();

                void makeGrid();
                int getGridIndex(glm::dvec2 /*pos*/);
                int getGridIndex(Particle /*particle*/);
                
                double getFrictionFactor(double /*dt*/);

                glm::dvec2 getRelativePosition(glm::dvec2 /*from*/, glm::dvec2 /*to*/); // to - from
                void shuffleParticle();
                int wrapGrid(int /*calculated*/, int /*bound*/);
        };
    }
}