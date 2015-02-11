#pragma once

#include "Manager.h"

//
// Title: Main
// Author: Jonathan DiGiacomo
// Version: 1.0.0
// 
// The application runner.
//

namespace graphics
{
	void init(int argc, char** argv, char* name);
	void update();
	void reshape(int width, int height);
	void keyboard(unsigned char, int, int);
}