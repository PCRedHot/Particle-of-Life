#include <GL/freeglut.h>
// #include <thread>
#include <cstdio>
#include <omp.h>

#include "app.h"

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT
    
    omp_set_num_threads(4);
    fprintf(stdout, "No of threads: %i\n", omp_get_num_threads());

    ParticleOfLifeApp::App app = ParticleOfLifeApp::App();
    app.launch();

    return 0;
}

