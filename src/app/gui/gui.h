#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace ParticleOfLifeApp {
	class AppGUI {
		public:
			~AppGUI();

			AppGUI(const GLFWwindow*);

			void scaleGui(float /*scale*/);
			void setIO(double /*dt*/, int /*width*/, int /*height*/);

			void destroyGUI();


		protected:
			
	};
}