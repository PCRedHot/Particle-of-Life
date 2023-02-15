#include <omp.h>
#include <math.h>
#include <algorithm>
#include <random>
#include <glm/vec2.hpp>

#include "particle.h"
#include "physics.h"
#include "interaction_matrix.h"

using namespace ParticleOfLife::Physics;

PhysicsSetting::PhysicsSetting() {
    interactionMatrix = InteractionMatrix(TYPE_SIZE);
}

PhysicsSetting::~PhysicsSetting() {
    
}

PhysicsSetting PhysicsSetting::deepCopy() {
    PhysicsSetting rtnCopy = PhysicsSetting();

    rtnCopy.interactionMatrix = interactionMatrix.deepCopy();
    rtnCopy.rMax = rMax;
    rtnCopy.velocityHalfLife = velocityHalfLife;
    rtnCopy.forceScale = forceScale;
    rtnCopy.wrap = wrap;

    return rtnCopy;
}

bool PhysicsSetting::operator==(PhysicsSetting o) {
    if (interactionMatrix != o.interactionMatrix) return false;

    if (rMax != o.rMax) return false;
    if (velocityHalfLife != o.velocityHalfLife) return false;
    if (forceScale != o.forceScale) return false;
    if (wrap != o.wrap) return false;

    return true;
}

bool PhysicsSetting::operator!=(PhysicsSetting o) {
    return !operator==(o);
}



PhysicsEngine::PhysicsEngine() {
    setting = PhysicsSetting();
    particles = std::vector<Particle>();
}

PhysicsEngine::~PhysicsEngine() {
    // delete[] particles;
}


void PhysicsEngine::calculateNxNy() {
    nx = (int) std::floor(2 / gridSize);
    ny = (int) std::floor(2 / gridSize);
}

void PhysicsEngine::generateInteractionMatrix() {
    setting.interactionMatrix.randomize(1);
}

int PhysicsEngine::getTypeCount() {
    return setting.interactionMatrix.size();
}

void PhysicsEngine::setParticleCount(int num) {
    while (particles.size() < num) {
        particles.push_back(Particle(getTypeCount()));
    }
    while (particles.size() > num) {
        particles.pop_back();
    }
    shuffleParticle();
}

void PhysicsEngine::simulate(double dt) {
    makeGrid();

    int nParticle = particles.size();
    #pragma omp parallel for
    for (int i = 0; i < nParticle; i++) {
        Particle p = particles[i];

        // Friction
        p.velocity *= getFrictionFactor(dt);

        int cx0 = (int) ((p.position.x + 1) / gridSize);
        int cy0 = (int) ((p.position.y + 1) / gridSize);

        for (glm::ivec2 neighborGrid : gridNeighborhood) {
            int cx = wrapGrid(cx0 + neighborGrid.x, nx);
            int cy = wrapGrid(cy0 + neighborGrid.y, ny);

            if (setting.wrap) {
                cx = wrapGrid(cx, nx);
                cy = wrapGrid(cy, ny);
            } else {
                if (cx < 0 || cx >= nx || cy < 0 || cy >= ny) continue; // Out of bound
            }

            int ci = cx + cy * nx;

            int start = ci == 0 ? 0 : grids[ci - 1];
            int stop = grids[ci];

            for (int j = start; j < stop; j++) {
                if (i == j) continue;

                Particle q = particles[j];

                // glm::dvec2 relativePos =    
                // TODO
            }
        }        
    }
}

double PhysicsEngine::getFrictionFactor(double dt) {
    if (setting.velocityHalfLife == 0) return 0;
    if (setting.velocityHalfLife == std::numeric_limits<double>::infinity()) return 1.0;

    return pow(0.5, dt / setting.velocityHalfLife);
}

void PhysicsEngine::makeGrid() {        // Put particles in the same grid together!
    gridSize = setting.rMax;
    if (prevGridSize != gridSize) calculateNxNy();
    prevGridSize = gridSize;

    // Init Arrays
    std::vector<int>(nx*ny, 0).swap(grids);

    for (Particle p : particles) {
        grids[getGridIndex(p)] += 1;
    }
    
    int offset = 0;
    for (int i = 0; i < grids.size(); i++) {
        int count = grids[i];
        grids[i] = offset;
        offset += count;
    }

    for (Particle p : particles) {
        int ci = getGridIndex(p);
        int i = grids[ci];
        particlesBuffer[i] = p;
        grids[ci]++;  // for next access
    }

    particlesBuffer.swap(particles);
}

int PhysicsEngine::getGridIndex(Particle particle) {
    return getGridIndex(particle.position);
}

int PhysicsEngine::getGridIndex(glm::dvec2 pos) {
    int cx = (int) ((pos.x + 1) / gridSize);
    int cy = (int) ((pos.y + 1) / gridSize);

    cx = std::min(cx, nx);
    cx = std::max(cx, 0);
    cy = std::min(cy, ny);
    cy = std::max(cy, 0);

    return cx + cy * nx;
}

void PhysicsEngine::shuffleParticle() {
    auto rd = std::random_device {}; 
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(particles), std::end(particles), rng);
}

int PhysicsEngine::wrapGrid(int c, int n) {
    if (c < 0) {
        return c + n;
    } else if (c >= n) {
        return c - n;
    } else {
        return c;
    }
}