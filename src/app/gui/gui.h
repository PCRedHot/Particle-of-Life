#pragma	once
#include <windows.h>
#include <GL/glut.h>  



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