#ifndef APP_H
#define APP_H

#include <windows.h>
#include <GL/glut.h>  

#include "gui.h"

namespace ParticleOfLifeApp {
	class App {
	public:
		~App();

		App();

		void launch();
		
		
		double tick();
		void processEvents();
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

void drawCallback();
void setupDrawCallback(ParticleOfLifeApp::App*);

#endif