#include <GL/freeglut.h>
// #include <thread>
#include <cstdio>
#include <omp.h>

#include "app.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT

    ParticleOfLifeApp::App app = ParticleOfLifeApp::App();
    app.launch();

    return 0;
}

