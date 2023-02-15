#include <cassert>
#include <algorithm>
#include <iterator> 
#include <glm/vec3.hpp>
#include <random>

#include "accelerator.h"
#include "interaction_matrix.h"

using namespace ParticleOfLife::Physics;


InteractionMatrix::InteractionMatrix() : InteractionMatrix::InteractionMatrix(1) {}

InteractionMatrix::InteractionMatrix(int size) {
    this->n = size;
    values = new double*[n];
    types = new AccelerateType*[n];
    for (int i = 0; i < n; i++) {
        values[i] = new double[n];
        types[i] = new AccelerateType[n];
    }
}

InteractionMatrix::~InteractionMatrix() {
    for (int i = 0; i < n; i++) {
        delete[] values[i];
        delete[] types[i];
    }
    delete[] values;
    delete[] types;
}

int InteractionMatrix::size() {
    return n;
}

double InteractionMatrix::getValue(int i, int j) {
    return values[i][j];
}

void InteractionMatrix::setValue(int i, int j, double v) {
    values[i][j] = v;
}

AccelerateType InteractionMatrix::getType(int i, int j) {
    return types[i][j];
}

void InteractionMatrix::setType(int i, int j, AccelerateType v) {
    types[i][j] = v;
}

void InteractionMatrix::randomize(double maxMag) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // values[i][j] = -maxMag + (rand() % static_cast<int>(2 * maxMag + 1));
            values[i][j] = -maxMag + 2 * maxMag * (double) rand() / RAND_MAX;
            types[i][j] = AccelerateType::UNIFORM;
        }
    }
}

InteractionMatrix InteractionMatrix::deepCopy() {
    InteractionMatrix rtnCopy = InteractionMatrix(n);

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