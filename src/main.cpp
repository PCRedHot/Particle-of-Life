#include <GL/freeglut.h>
// #include <thread>
#include <omp.h>

#include "app.h"

int main(int argc, char** argv) {
    fprintf(stdout, "Start\n");
    glutInit(&argc, argv);                 // Initialize GLUT
    fprintf(stdout, "Init Done\n");

    ParticleOfLifeApp::App app = ParticleOfLifeApp::App();
    app.launch();

    fprintf(stdout, "Ended\n");
    return 0;
}