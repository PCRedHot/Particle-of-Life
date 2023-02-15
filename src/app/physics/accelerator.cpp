#include <cmath>
#include <glm/vec2.hpp>

#include "accelerator.h"

// #define PI 3.1415

using namespace ParticleOfLife::Physics;

std::map<AccelerateType, Accelerator> ParticleOfLife::Physics::acceleratorTypeMap = {
    {AccelerateType::UNIFORM, UniformAccelerator()},
    {AccelerateType::INVERSE, InverseAccelerator()},
    {AccelerateType::INVERSE_SQUARE, InverseSquareAccelerator()},
    {AccelerateType::INVERSE_CUBE, InverseCubeAccelerator()},
    {AccelerateType::ROTATE_90, Rotate90Accelerator()},
};

glm::dvec2 ParticleOfLife::Physics::accelerate(AccelerateType type, double typeInteraction, glm::dvec2 relativePos) {
    Accelerator typeAccelerator = acceleratorTypeMap[type];
    return typeAccelerator.accelerate(typeInteraction, relativePos);
}

glm::dvec2 Accelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = relativePos.length();
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist)) / (1 - rMin);
    return relativePos * (force / dist);
}

glm::dvec2 UniformAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = relativePos.length();
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist)) / (1 - rMin);
    return relativePos * (force / dist);
}

glm::dvec2 InverseAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = relativePos.length();
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist)) / (1 - rMin);
    return relativePos * (force / (dist * dist));
}

glm::dvec2 InverseSquareAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = relativePos.length();
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist)) / (1 - rMin);
    return relativePos * (force / (dist * dist * dist));
}

glm::dvec2 InverseCubeAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = relativePos.length();
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist)) / (1 - rMin);
    return relativePos * (force / (dist * dist * dist * dist));
}

glm::dvec2 Rotate90Accelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double dist = relativePos.length();
    double force = 1 - dist;
    glm::dvec2 delta = glm::dvec2(-relativePos.y, relativePos.x);
    return delta * (force / dist);
}