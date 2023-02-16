// #include <windows.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glut.h"
#include "imgui/backends/imgui_impl_opengl3.h"
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

void idleCallback() {
	currentInstance->idleLoop();
}

void mouseCallback(int button, int state, int x, int y) {
	currentInstance->onMouse(button, state, x, y);
}

void reshapeCallback(int width, int height) {
    currentInstance->windowWidth = width;
    currentInstance->windowHeight = height;
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
    // fprintf(stdout, "Making physicsEngine\n");
    physicsEngine = new ParticleOfLife::Physics::PhysicsEngine();
    physicsEngine->setParticleCount(40000);
}

App::~App() {
 
}


double App::tick() {
    int curTime = glutGet(GLUT_ELAPSED_TIME);
    // fprintf(stdout, "tick(): %i...", curTime);
    double dt = curTime - lastFrameTime;
    lastFrameTime = curTime;
    return isPlaying ? dt / 1000 : 0;
}




void App::launch() {
    /* Initialize the library (in case) */
    // fprintf(stdout, "Launching\n");
    init("Particle of Life", false);
    // fprintf(stdout, "Launching Init done\n");
    
    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void App::init(const char* title, bool fullscreen) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Window Creation
    int monitorWidth = glutGet(GLUT_SCREEN_WIDTH);
    int monitorHeight = glutGet(GLUT_SCREEN_HEIGHT);

    double f = 0.2;
    windowPosX = (int)(f * monitorWidth / 2);
    windowPosY = (int)(f * monitorHeight / 2);
    windowWidth = (int)((1 - f) * monitorWidth);
    windowHeight = (int)((1 - f) * monitorHeight);

    // boxWidth = windowWidth;
    // boxHeight = windowHeight;

    // fprintf(stdout, "screen - width: %i, height: %i, x: %i, y: %i\n", monitorWidth, monitorHeight, windowPosX, windowPosY);
    // fprintf(stdout, "window - width: %i, height: %i\n", width, height);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowPosX, windowPosY);
    
    glutCreateWindow(title);
    // glutFullScreen();

    setCurrentInstance(this);
    ::glutDisplayFunc(drawCallback);
    ::glutIdleFunc(idleCallback);
    ::glutReshapeFunc(reshapeCallback);
    ::glutMouseFunc(mouseCallback);
    ::glutKeyboardFunc(keyboardNormalCallback);
    ::glutSpecialFunc(keyboardSpecialCallback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();

    ImGui_ImplGLUT_InstallFuncs();
}

void App::drawLoop() {
     // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    {   // GUI
        ImGui::SetNextWindowSize(ImVec2(500, 0));
        ImGui::Begin("Controls");

        ImGui::Text("Types:");
        
        for (int i = 0; i < physicsEngine->setting.typeCount; i++) {
            if (ImGui::Button("X")) {}
            ImGui::SameLine();
            ImGui::ColorEdit3(std::to_string(i).c_str(), physicsEngine->setting.typeColour[i]);
        }
        ImVec2 v = ImGui::GetWindowSize();  // v = {32, 48} ,   is tool small
ImGui::Text("%f %f", v.x, v.y);
if (ImGui::GetFrameCount() < 10)
    printf("Frame %d: Size %f %f\n", ImGui::GetFrameCount(), v.x, v.y);
ImGui::End();
    }

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer

    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    // fprintf(stdout, "Drawing %i Particles\n", (int) physicsEngine->particles.size());
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    int size = std::min(windowWidth, windowHeight);

    int x = (windowWidth - size) / 2;
    int y = (windowHeight - size) / 2;

    glViewport(x, y, size, size);

    

    glBegin(GL_POINTS);
    for (int i = 0; i < physicsEngine->particles.size(); i++) {
        ParticleOfLife::Particle p = physicsEngine->particles[i];
        float* colour = physicsEngine->setting.typeColour[p.type];
        glColor3f(colour[0], colour[1], colour[3]);
        glVertex2d(p.position.x, p.position.y);        
    }
    glEnd();


    glFlush();
    glutSwapBuffers();    
}

void App::idleLoop() {
    double dt = tick();

    try {
        // fprintf(stdout, "Simulating dt = %f... ", dt);
        physicsEngine->simulate(dt);
        // fprintf(stdout, "Done\n");
    } catch (...) {
        fprintf(stderr, "ERROR when simulating\n");
    }
    
    glutPostRedisplay();
}


void App::onMouse(int button, int state, int x, int y) {
	fprintf(stdout, "Mouse Wheel: %i, %i, %i, %i\n", button, state, x, y);
    

    // zoom += direction * 0.1;
    // zoom = std::max(zoom, minZoom);    
    // zoom = std::min(zoom, maxZoom);    
}

void App::onPressNormalKey(unsigned char key, int x, int y) {
    fprintf(stdout, "Normal Pressed: %u (%i, %i)\n", key, x, y);

    if (key == 27) glutLeaveMainLoop();

    if (key == 32) isPlaying = !isPlaying;

}

void App::onPressSpecialKey(int key, int x, int y) {
    fprintf(stdout, "Special Pressed: %i (%i, %i)\n", key, x, y);
}