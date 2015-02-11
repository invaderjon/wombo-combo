#pragma once

#include <iostream>
#include <stdio.h>
#include "graphics.h"

namespace graphics
{
	class Manager
	{
	public:
		Manager();
		~Manager();
		void init(int argc, char** argv);
		int start(const char* windowTitle);
	};

	void display();
	void idle();
	void reshape(int width, int height);
	void keyboard(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void motion(int x, int y);
}