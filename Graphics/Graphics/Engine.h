#pragma once

#include <chrono>
#include <sstream>
#include <string>
#include <cimg\CImg.h>
#include "Graphics.h"
#include "InputManager.h"
#include "InputPrinter.h"
#include "Program.h"
#include "HeightMap.h"
#include "ShaderStructs.h"
#include "Camera.h"
#include "ArcBallCamera.h"
#include "Buffers.h"
#include "Texture.h"
#include "Octree.h"

#define TARGET_FRAME_TIME 16666667

using namespace cimg_library;

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
		GEenum initGLEW();
		void initGL();
		void initEngine();
		void loadHeightMap();
		void loop();
		void update();
		void render();
		void measure();
		static void resize(GLFWwindow* window, GEint width, GEint height);
		static void onBufferResized(GLFWwindow* window, GEint width, GEint height);
		static void onErrorReceived(int error, const char* description);

		char* title = DEFAULT_WINDOW_TITLE;
		int width = DEFAULT_WINDOW_WIDTH;
		int height = DEFAULT_WINDOW_HEIGHT;
		float ratio = width / (float)height;
		GLFWwindow* mWindow;
		InputManager* mInputManager;
		Camera* mCamera;
		//ShaderIndices mHMIndices;
		//ShaderIndices mOTIndices;
		Program* mHMProgram;
		Program* mOTProgram;
		HeightMap* mHeightMap;
		Octree* mOctree;
	};
}
