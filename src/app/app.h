#pragma	once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "gui/gui.h"

namespace ParticleOfLifeApp {
	class App {
	public:
		~App();

		App();
		App(int /*width*/, int /*height*/);

		void launch();
		
		double getDeltaTime();
		void processEvents();
		void draw(double /*dt*/);

	protected:
		GLFWwindow* window;
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
		double lastFrameTime = -1;
	
	private:
		void init(const char* /*title*/, bool /*fullscreen*/);
		
		double zoom = 1;
		//glm::
		
	};
}
