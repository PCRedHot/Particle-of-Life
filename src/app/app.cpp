// #include <windows.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <stdlib.h>
#include <stdio.h>

#include "app.h"
#include "physics/physics.h"
#include "physics/particle.h"

ParticleOfLifeApp::App* currentInstance = nullptr;

void setCurrentInstance(ParticleOfLifeApp::App* app) {
	currentInstance = app;
}

void drawCallback() {
	currentInstance->drawLoop();
}

void keyboardNormalCallback(unsigned char key, int x, int y) {
    currentInstance->onPressNormalKey(key, x, y);
}

void keyboardSpecialCallback(int key, int x, int y) {
    currentInstance->onPressSpecialKey(key, x, y);
}


using namespace ParticleOfLifeApp;

App::App() {
    fprintf(stdout, "Making App\n");
    fprintf(stdout, "Making physicsEngine\n");
    physicsEngine = ParticleOfLife::Physics::PhysicsEngine();
    physicsEngine.setParticleCount(100);
}

App::~App() {
 
}


double App::tick() {
    int curTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = curTime - lastFrameTime;
    lastFrameTime = curTime;
    return isPlaying ? dt / 1000 : 0;
}




void App::launch() {
    /* Initialize the library (in case) */
    fprintf(stdout, "Launching\n");
    init("Particle of Life", false);
    fprintf(stdout, "Launching Init done\n");
    
    glutMainLoop();
}

void App::init(const char* title, bool fullscreen) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Window Creation
    int monitorWidth = glutGet(GLUT_SCREEN_WIDTH);
    int monitorHeight = glutGet(GLUT_SCREEN_HEIGHT);

    fprintf(stdout, "a");

    double f = 0.2;
    windowPosX = (int)(f * monitorWidth / 2);
    windowPosY = (int)(f * monitorHeight / 2);
    windowWidth = (int)((1 - f) * monitorWidth);
    windowHeight = (int)((1 - f) * monitorHeight);

    width = windowWidth;
    height = windowHeight;

    fprintf(stdout, "screen - width: %i, height: %i, x: %i, y: %i\n", monitorWidth, monitorHeight, windowPosX, windowPosY);
    fprintf(stdout, "window - width: %i, height: %i\n", width, height);

    glutInitWindowSize(width, height);
    glutInitWindowPosition(windowPosX, windowPosY);
    
    fprintf(stdout, "1");
    glutCreateWindow(title);
    // glutFullScreen();

    setCurrentInstance(this);
    ::glutDisplayFunc(drawCallback);
    ::glutKeyboardFunc(keyboardNormalCallback);
    ::glutSpecialFunc(keyboardSpecialCallback);
    fprintf(stdout, "2");

}


void App::drawLoop() {
    double dt = tick();

    // try {
    //     // physicsEngine->simulate(dt);
    // } catch (...) {
    //     fprintf(stderr, "ERROR when simulating");
    // }
    

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    // Draw a Red 1x1 Square centered at origin
    int width = glutGet(GLUT_SCREEN_WIDTH);
    int height = glutGet(GLUT_SCREEN_HEIGHT);
    float r = 2.0f;
    
    float rdx = r / width;
    float rdy = r / height;
    for (ParticleOfLife::Particle p : physicsEngine.particles) {
        glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
            glColor3f(1.0f, 0.0f, 0.0f); // Red
            glVertex2f(p.position.x - rdx, p.position.y - rdy);    // x, y
            glVertex2f(p.position.x + rdx, p.position.y - rdy);    // x, y
            glVertex2f(p.position.x + rdx, p.position.y + rdy);    // x, y
            glVertex2f(p.position.x - rdx, p.position.y + rdy);    // x, y
            // glVertex2f( 0.5f, -0.5f);
            // glVertex2f( 0.5f,  0.5f);
            // glVertex2f(-0.5f,  0.5f);
        glEnd();
    }
    
    glutSwapBuffers();    
}

void App::onPressNormalKey(unsigned char key, int x, int y) {
    fprintf(stdout, "Normal Pressed: %u (%i, %i)\n", key, x, y);

    // if (key == 27) glutLeaveMainLoop();
}

void App::onPressSpecialKey(int key, int x, int y) {
    fprintf(stdout, "Special Pressed: %i (%i, %i)\n", key, x, y);
}