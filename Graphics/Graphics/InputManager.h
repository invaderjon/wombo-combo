#pragma once
#include <mutex>
#include <list>
#include "Platform.h"
#include "Input.h"
#include "IControllable.h"

//
// Title: InputManager
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Process all user input and notifies all relevant
// listeners. To access use getInstance().
//

using namespace std;

namespace graphics
{
	class InputManager
	{
	public:
		// global methods
		static InputManager* getInstance();
		static void onKeyboardInput(GLFWwindow* window, int key, int scanCode, int action, int mods);
		static void onMouseEnter(GLFWwindow* window, int entered);
		static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
		static void onMouseMove(GLFWwindow* window, double xpos, double ypos);
		static void onScroll(GLFWwindow* window, double xoffset, double yoffset);
		static void onFileDropped(GLFWwindow* window, int count, const char** names);

		// local methods
		void addListener(IControllable* listener);
		void removeListener(IControllable* listener);
		void onCursorMove(Cursor cursor);
		void onInput(int key, int action, int mods);
		void onClick(int button, int action, int mods);
		void onScroll(double xoffset, double yoffset);
	protected:
		InputManager();
		~InputManager();
	private:
		// global
		static InputManager* sInstance;

		// local
		mutex mMtx;
		list<IControllable*> mListeners;
	};
}