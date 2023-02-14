#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "app.h"

using namespace ParticleOfLifeApp;

App::App() : App(640, 480) {}        // Default Windown Size

App::App(int w, int h) :
    width(w),
    height(h)
{

	
}

App::~App() {
 
	glfwTerminate();
}


double App::getDeltaTime() {
    return isPlaying ? glfwGetTime() - lastFrameTime : 0;
}

void App::processEvents() {

}

void App::launch() {
    /* Initialize the library (in case) */
    init("Particle of Life", false);

    /* App display setup */
    gui = new AppGUI(window);
    guiScale = (float) height / 1000;


    lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {

        preMouseX = mouseX;
        preMouseY = mouseY;
             

        /* Poll for and process events */
        glfwPollEvents();
        processEvents();


        /* Rendering */
        double dt = getDeltaTime();
        gui->setIO(dt, width, height);
        draw(dt);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        lastFrameTime = glfwGetTime();
	}
}

void App::init(const char* title, bool fullscreen) {
    if (glewInit() != GLEW_OK) fprintf(stderr, "Error setting up GLEW");
    else fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Window Creation
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

    int monitorWidth = videoMode->width;
    int monitorHeight = videoMode->height;

    double f = 0.2;
    windowPosX = (int)(f * monitorWidth / 2);
    windowPosY = (int)(f * monitorHeight / 2);
    windowWidth = (int)((1 - f) * monitorWidth);
    windowHeight = (int)((1 - f) * monitorHeight);

    width = windowWidth;
    height = windowHeight;

    fprintf(stdout, "width: %i, height: %i\n", width, height);
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);  // Enable v-sync

    // Make the window visible
    glfwShowWindow(window);
}


void App::draw(double dt) {



}