#include <cassert>
#include <algorithm>
#include <iterator> 
#include <glm/vec3.hpp>
#include <random>
#include <string>

#include "accelerator.h"
#include "interaction_matrix.h"

using namespace ParticleOfLife::Physics;


InteractionMatrix::InteractionMatrix() : InteractionMatrix::InteractionMatrix(1) {}

InteractionMatrix::InteractionMatrix(int size) {
    this->n = size;
    values = new float[n*n];
    types = new AccelerateType[n*n];
    
    resetType();
}

InteractionMatrix::~InteractionMatrix() {
    delete[] values;
    delete[] types;
}

int InteractionMatrix::size() {
    return n;
}

float InteractionMatrix::getValue(int i, int j) {
    // if (isSymmetric && j > i) return values[j*n + i]; 
    return values[i*n+j];
}

float* InteractionMatrix::getValuePointer(int i, int j) {
    if (isSymmetric && j > i) return &(values[j*n + i]); 
    return &(values[i*n+j]);
}

void InteractionMatrix::setValue(int i, int j, double v) {
    if (isSymmetric && j > i) values[j*n+i] = v;
    values[i*n+j] = v;
}

AccelerateType InteractionMatrix::getType(int i, int j) {
    if (isSymmetric && j > i) return types[j*n + i]; 
    return types[i*n+j];
}

void InteractionMatrix::setType(int i, int j, AccelerateType v) {
    if (isSymmetric && j > i) types[j*n+i] = v;
    types[i*n+j] = v;
    // if (isSymmetric) types[j*n+i] = v;
}

void InteractionMatrix::randomizeValue(double maxMag) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            values[i*n+j] = (2 * maxMag) * ((double) rand() / (double) RAND_MAX) - maxMag;
        }
    }
}

void InteractionMatrix::resetValue() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            values[i*n+j] = 0.0f;
        }
    }
}

void InteractionMatrix::resetType() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) types[i*n+j] = AccelerateType::UNIFORM;
            else types[i*n+j] = AccelerateType::INVERSE;
        }
    }
}

void InteractionMatrix::setSymmetric(bool v) {
    isSymmetric = v;
}

bool* InteractionMatrix::getSymmetricControlPointer() {
    return &isSymmetric;
}

InteractionMatrix InteractionMatrix::deepCopy() {
    InteractionMatrix rtnCopy = InteractionMatrix(n);

    rtnCopy.setSymmetric(isSymmetric);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rtnCopy.setValue(i, j, getValue(i, j));
            rtnCopy.setType(i, j, getType(i, j));
        }
    }
    
    return rtnCopy;
}

InteractionMatrix InteractionMatrix::extract(int *indices){
    int newSize = sizeof(indices)/sizeof(int);
    assert (newSize > 0 && "Extracted Matrix has negative size!");

    InteractionMatrix rtnMatrix = InteractionMatrix(newSize);
    
    int ni = 0, nj = 0;
    for (int i = 0; i < size(); i++) {
        bool existsI = std::any_of(indices, indices + newSize, [&](int v) {
            return v == i;
        });
        if (!existsI) continue;
                
        nj = 0;
        for (int j = 0; j < size(); j++) {
            bool existsJ = std::any_of(indices, indices + newSize, [&](int v) {
                return v == j;
            });
            if (!existsJ) continue;

            rtnMatrix.setValue(ni, nj, getValue(i, j));
            rtnMatrix.setType(ni, nj, getType(i, j));

            nj += 1;
        }
        ni += 1;
    }

    return rtnMatrix;
}

bool InteractionMatrix::operator==(InteractionMatrix o) {
    if (n != o.n) return false;

    if (o.isSymmetric != isSymmetric) return false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (getValue(i, j) != o.getValue(i, j)) return false;
            if (getType(i, j) != o.getType(i, j)) return false;
        }
    }

    return true;
}

bool InteractionMatrix::operator!=(InteractionMatrix o) {
    return !operator==(o);
}