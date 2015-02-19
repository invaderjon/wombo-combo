#pragma once

#include "Graphics.h"
#include "InputManager.h"
#include "InputPrinter.h"

//
// Title: Engine
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Creates the window and manages the render loop and processes user input.
//

namespace graphics
{
	class Engine
	{

	public:
		Engine();
		~Engine();
		int start(int argc, char** argv);

	private:
		int parseArgs(int argc, char** argv);
		int initGLFW();
		void initGL();
		void loop();
		void render();
		void measure();
		static void onErrorReceived(int error, const char* description);

		char* title = DEFAULT_WINDOW_TITLE;
		int width = DEFAULT_WINDOW_WIDTH;
		int height = DEFAULT_WINDOW_HEIGHT;
		float ratio = width / (float)height;
		GLFWwindow* window;
		InputManager* inputManager;
	};
}