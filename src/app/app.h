#pragma	once

// #include <windows.h>
#include <GL/freeglut.h>

#include "gui.h"
#include "physics/physics.h"

namespace ParticleOfLifeApp {
	class App {
	public:
		~App();

		App();

		ParticleOfLife::Physics::PhysicsEngine physicsEngine;

		void launch();
		
		
		double tick();
		// void processEvents();

		void onPressNormalKey(unsigned char /*key*/, int /*x*/, int /*y*/);
		void onPressSpecialKey(int /*key*/, int /*x*/, int /*y*/);

		void drawLoop();

	protected:
		int window;
		int width, height;
		double mouseX = -1, mouseY = -1;
		double preMouseX = mouseX, preMouseY = mouseY;
						
		AppGUI* gui;
		float guiScale = 1.0f;

		// Window State
		int windowPosX = -1, windowPosY = -1;
		int windowWidth = -1, windowHeight = -1;
	
			
		// Simulation State
		bool isPlaying = false;
		int lastFrameTime = -1;
	
	private:
		

		void init(const char* /*title*/, bool /*fullscreen*/);
		
		double zoom = 1;
		
	};

	
}


extern ParticleOfLifeApp::App* currentInstance;

void setCurrentInstance(ParticleOfLifeApp::App*);

void drawCallback();
void keyboardNormalCallback(unsigned char /*key*/, int /*x*/, int /*y*/);
void keyboardSpecialCallback(int /*key*/, int /*x*/, int /*y*/);
// void setupDrawCallback();

