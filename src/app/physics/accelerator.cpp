#include <cmath>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <cstdio>
#include <string>

#include "accelerator.h"

// #define PI 3.1415

using namespace ParticleOfLife::Physics;

// std::map<AccelerateType, Accelerator*> ParticleOfLife::Physics::acceleratorTypeMap = {
//     {AccelerateType::UNIFORM, new UniformAccelerator()},
//     {AccelerateType::INVERSE, new InverseAccelerator()},
//     {AccelerateType::INVERSE_SQUARE, new InverseSquareAccelerator()},
//     {AccelerateType::INVERSE_CUBE, new InverseCubeAccelerator()},
//     {AccelerateType::ROTATE_90, new Rotate90Accelerator()},
// };

std::string ParticleOfLife::Physics::getAccelerateTypeString(AccelerateType type) {
    switch (type) {
        default:
        case AccelerateType::UNIFORM: return "Uniform Acceleration";        
        case AccelerateType::INVERSE: return "Distance Inverse Acceleration";        
        case AccelerateType::INVERSE_SQUARE: return "Distance Inverse Square Acceleration";  
        case AccelerateType::INVERSE_CUBE: return "Distance Inverse Cube Acceleration";  
        case AccelerateType::ROTATE_90: return "Rotate 90 Acceleration";
    }
}

glm::dvec2 ParticleOfLife::Physics::accelerate(AccelerateType type, double typeInteraction, glm::dvec2 relativePos) {
    // Accelerator* typeAccelerator = acceleratorTypeMap[type];
    // return typeAccelerator->accelerate(typeInteraction, relativePos);
    switch (type) {
        default:
        case AccelerateType::UNIFORM: return UniformAccelerator::accelerate(typeInteraction, relativePos);        
        case AccelerateType::INVERSE: return InverseAccelerator::accelerate(typeInteraction, relativePos);        
        case AccelerateType::INVERSE_SQUARE: return InverseSquareAccelerator::accelerate(typeInteraction, relativePos);        
        case AccelerateType::INVERSE_CUBE: return InverseCubeAccelerator::accelerate(typeInteraction, relativePos);        
        case AccelerateType::ROTATE_90: return Rotate90Accelerator::accelerate(typeInteraction, relativePos);        
    }
}

std::string ParticleOfLife::Physics::getAccelerateTypeDescription() {
    std::string rtnString = "";
    for (int i = 0; i < (int)AccelerateType::Count; i++) {
        rtnString.append(std::to_string(i).append(": "));
        rtnString.append(ParticleOfLife::Physics::getAccelerateTypeString((AccelerateType) i));
        rtnString.append("\n");
    }
    return rtnString;
}

// glm::dvec2 Accelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
//     double rMin = 0.3;
//     double dist = glm::length(relativePos);
//     double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist) / (1 - rMin));
//     fprintf(stdout, "Base F: %f\n", force);
//     return relativePos * (force / dist);
// }

glm::dvec2 UniformAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = glm::length(relativePos);
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist) / (1 - rMin));
    // fprintf(stdout, "Uniform Interaction: %F, F: %f, Dist: %f\n", typeInteraction, force, dist);
    return relativePos * (force / dist);
}

glm::dvec2 InverseAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = glm::length(relativePos);
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist) / (1 - rMin));
    // if (glm::isnan(force)) fprintf(stderr, "interaction factor: %f, dist: %f", typeInteraction, dist);
    // fprintf(stdout, "Inverse F: %f\n", force);
    return relativePos * (force / (dist * dist));
}

glm::dvec2 InverseSquareAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = glm::length(relativePos);
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist) / (1 - rMin));
    return relativePos * (force / (dist * dist * dist));
}

glm::dvec2 InverseCubeAccelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double rMin = 0.3;
    double dist = glm::length(relativePos);
    double force = dist < rMin ? (dist / rMin - 1) : typeInteraction * (1 - std::abs(1 + rMin - 2 * dist) / (1 - rMin));
    return relativePos * (force / (dist * dist * dist * dist));
}

glm::dvec2 Rotate90Accelerator::accelerate(double typeInteraction, glm::dvec2 relativePos) {
    double dist = glm::length(relativePos);
    double force = 1 - dist;
    glm::dvec2 delta = glm::dvec2(-relativePos.y, relativePos.x);
    return delta * (force / dist);
}