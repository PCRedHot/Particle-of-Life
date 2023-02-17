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
    physicsEngine->setParticleCount(DEFAULT_PARTICLE_NUM);
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

    double f = 0.5;
    windowPosX = (int)(f * monitorWidth / 2);
    windowPosY = (int)(f * monitorHeight / 2);
    windowWidth = (int)((1 - f) * monitorWidth);
    windowHeight = (int)((1 - f) * monitorHeight);

    int size = std::min(windowWidth, windowHeight);

    // boxWidth = windowWidth;
    // boxHeight = windowHeight;

    // fprintf(stdout, "screen - width: %i, height: %i, x: %i, y: %i\n", monitorWidth, monitorHeight, windowPosX, windowPosY);
    // fprintf(stdout, "window - width: %i, height: %i\n", width, height);

    glutInitWindowSize(size, size);
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

bool show_demo_window = true;

void App::drawLoop() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer


    
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
        glColor3f(colour[0], colour[1], colour[2]);
        glVertex2d(p.position.x, p.position.y);        
    }
    glEnd();


    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    ImGui::ShowDemoWindow(&show_demo_window);

    int typeCount = physicsEngine->setting.typeCount;
    {   // Control GUI
        ImGui::SetNextWindowSize(ImVec2(500, 0));
        ImGui::Begin("Controls");
        if (ImGui::CollapsingHeader("Parameters")) {
            ImGui::InputInt("Number of Particles", &_inputParticleNum);
            ImGui::SameLine();
            if (ImGui::Button("Apply")) {
                physicsEngine->setParticleCount(_inputParticleNum);
            } 
        }

        if (ImGui::CollapsingHeader("Particle Types")) {
            for (int i = 0; i < typeCount; i++) {
                ImGui::PushID(i);
                if (ImGui::Button("X")) {
                    // TODO delete type i
                }
                ImGui::SameLine();
                // float* colour = physicsEngine->setting.typeColour[i];
                // bool open_popup = ImGui::ColorButton("", ImVec4(colour[0], colour[1], colour[2], colour[3]), misc_flags);
                ImGui::ColorEdit3(std::string("Type ").append(std::to_string(i)).c_str(), physicsEngine->setting.typeColour[i], ImGuiColorEditFlags_NoLabel);
                ImGui::PopID();
            }
        }

        if (ImGui::CollapsingHeader("Interactions")) {
            ImGui::SeparatorText("Options");
            ImGui::Checkbox("Symmetric Interactions", physicsEngine->setting.interactionMatrix.getSymmetricControlPointer());
            ImGui::SeparatorText("Interaction Mode");
            ImGui::PushID("Mode");
            if (ImGui::Button("Reset")) physicsEngine->setting.interactionMatrix.resetType();
            static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_NoHostExtendX;
            if (ImGui::BeginTable("Interaction Mode", typeCount + 1, flags)) {
                for (int row = 0; row < typeCount + 1; row++) {
                    ImGui::TableNextRow();

                    if (row == 0) {     // First Row
                        for (int column = 1; column < typeCount + 1; column++) {
                            ImGui::TableSetColumnIndex(column);
                            // ImGui::Text("Type %c", '0' + column);
                            ImGui::Text(" ");

                            float* typeColour = physicsEngine->setting.typeColour[column-1];
                            ImU32 cellBgColour = ImGui::GetColorU32(ImVec4(typeColour[0], typeColour[1], typeColour[2], 1.0f));
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cellBgColour, column);
                        }
                    } else {
                        for (int column = 0; column < typeCount + 1; column++) {
                            ImGui::TableSetColumnIndex(column);

                            if (column == 0) { // First Column
                                ImGui::Text(" ");

                                float* typeColour = physicsEngine->setting.typeColour[row-1];
                                ImU32 cellBgColour = ImGui::GetColorU32(ImVec4(typeColour[0], typeColour[1], typeColour[2], 1.0f));
                                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cellBgColour, column);
                            } else {
                                int matrixI = row - 1;
                                int matrixJ = column - 1;

                                ImGui::PushID(matrixI);
                                ImGui::PushID(matrixJ);
                                ParticleOfLife::Physics::AccelerateType curType = physicsEngine->setting.interactionMatrix.getType(matrixI, matrixJ);
                                if (ImGui::Button(std::to_string((int) curType).c_str())) {
                                    physicsEngine->setting.interactionMatrix.setType(
                                        matrixI, matrixJ, 
                                        (ParticleOfLife::Physics::AccelerateType) (((int) curType + 1) % (int) ParticleOfLife::Physics::AccelerateType::Count)
                                    );
                                }
                                ImGui::PopID();
                                ImGui::PopID();
                            }
                        }
                    }                    
                }
                ImGui::EndTable();
                ImGui::SameLine();

                ImGui::TextWrapped("%s", ParticleOfLife::Physics::getAccelerateTypeDescription().c_str());
            }
            ImGui::PopID();
            
            ImGui::SeparatorText("Interaction Factor");
            ImGui::PushID("Factor");
            if (ImGui::Button("Reset")) physicsEngine->setting.interactionMatrix.resetValue();
            ImGui::SameLine();
            if (ImGui::Button("Randomize")) physicsEngine->setting.interactionMatrix.randomizeValue(1);
            if (ImGui::BeginTable("Interaction Factor", typeCount + 1, flags)) {
                for (int row = 0; row < typeCount + 1; row++) {
                    ImGui::TableNextRow();

                    if (row == 0) {     // First Row
                        for (int column = 1; column < typeCount + 1; column++) {
                            ImGui::TableSetColumnIndex(column);
                            // ImGui::Text("Type %c", '0' + column);
                            ImGui::Text(" ");

                            float* typeColour = physicsEngine->setting.typeColour[column-1];
                            ImU32 cellBgColour = ImGui::GetColorU32(ImVec4(typeColour[0], typeColour[1], typeColour[2], 1.0f));
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cellBgColour, column);
                        }
                    } else {
                        for (int column = 0; column < typeCount + 1; column++) {
                            ImGui::TableSetColumnIndex(column);

                            if (column == 0) { // First Column
                                ImGui::Text(" ");

                                float* typeColour = physicsEngine->setting.typeColour[row-1];
                                ImU32 cellBgColour = ImGui::GetColorU32(ImVec4(typeColour[0], typeColour[1], typeColour[2], 1.0f));
                                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cellBgColour, column);
                            } else {
                                int matrixI = row - 1;
                                int matrixJ = column - 1;

                                ImGui::PushID(matrixI);
                                ImGui::PushID(matrixJ);
                                ImGui::SetNextItemWidth(40);
                                float curType = physicsEngine->setting.interactionMatrix.getValue(matrixI, matrixJ);
                                // ImGui::DragFloat(std::to_string(curType).c_str(), physicsEngine->setting.interactionMatrix.getValuePointer(matrixI, matrixJ), 0.005f, -1.0f, 1.0f, "%.3f");
                                ImGui::DragFloat("", physicsEngine->setting.interactionMatrix.getValuePointer(matrixI, matrixJ), 0.005f, -1.0f, 1.0f, "%.2f");
                                ImGui::PopID();
                                ImGui::PopID();
                            }
                        }
                    }                    
                }
                ImGui::EndTable();
            }
            ImGui::PopID();
        }
        
        ImGui::End();
    }

    // Rendering 
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    glFlush();
    glutSwapBuffers();    
}

void App::idleLoop() {
    double dt = tick();

    try {
        // fprintf(stdout, "Simulating dt = %f... ", dt);
        // physicsEngine->simulate(dt);
        double maxDt = 25.0 / 1000;
        physicsEngine->simulate(std::min(dt, maxDt));
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