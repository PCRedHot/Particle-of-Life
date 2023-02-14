#include <windows.h>
#include <GL/glut.h>  
#include <stdlib.h>
#include <stdio.h>

#include "app.h"

ParticleOfLifeApp::App* currentInstance = nullptr;

void drawCallback() {
	currentInstance->drawLoop();
}

void setupDrawCallback(ParticleOfLifeApp::App* app) {
	currentInstance = app;
	::glutDisplayFunc(drawCallback);
}

using namespace ParticleOfLifeApp;

App::App() {

}

App::~App() {
 
	// glfwTerminate();
}


double App::tick() {
    int curTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = curTime - lastFrameTime;
    lastFrameTime = curTime;
    return isPlaying ? dt / 1000 : 0;
}

void App::processEvents() {

}



void App::launch() {
    /* Initialize the library (in case) */
    init("Particle of Life", false);

    glutMainLoop();

    /* App display setup */
    // gui = new AppGUI(window);
    // guiScale = (float) height / 1000;


    // lastFrameTime = glfwGetTime();

	// while (!glfwWindowShouldClose(window)) {

    //     preMouseX = mouseX;
    //     preMouseY = mouseY;
             

    //     /* Poll for and process events */
    //     glfwPollEvents();
    //     processEvents();


    //     /* Rendering */
    //     double dt = tick();
    //     gui->setIO(dt, width, height);
    //     drawLoop(dt);


    //     /* Swap front and back buffers */
    //     glfwSwapBuffers(window);

    //     lastFrameTime = glfwGetTime();
	// }
}

void App::init(const char* title, bool fullscreen) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    
    glutCreateWindow("Particle of Life");

    // Window Creation
    int monitorWidth = glutGet(GLUT_SCREEN_WIDTH);
    int monitorHeight = glutGet(GLUT_SCREEN_HEIGHT);

    double f = 0.2;
    windowPosX = (int)(f * monitorWidth / 2);
    windowPosY = (int)(f * monitorHeight / 2);
    windowWidth = (int)((1 - f) * monitorWidth);
    windowHeight = (int)((1 - f) * monitorHeight);

    width = windowWidth;
    height = windowHeight;

    fprintf(stdout, "width: %i, height: %i\n", width, height);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);

    setupDrawCallback(this);    

    // window = glfwCreateWindow(width, height, title, NULL, NULL);

    // glfwMakeContextCurrent(window);

    // glfwSwapInterval(1);  // Enable v-sync

    // // Make the window visible
    // glfwShowWindow(window);
}


void App::drawLoop() {
    double dt = tick();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    // Draw a Red 1x1 Square centered at origin
    glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-0.5f, -0.5f);    // x, y
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();

    glutSwapBuffers();    
}