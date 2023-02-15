#include <random>

#include "particle.h"

using namespace ParticleOfLife;

Particle::Particle() : Particle::Particle(1) {}

Particle::Particle(int numType) {
    position.x = -1 + 2 * (double) rand() / RAND_MAX;
    position.y = -1 + 2 * (double) rand() / RAND_MAX;

    type = rand() % numType;
}