#pragma once

#include "Constants.h"

//
// Title: Platform
// Author: Jonathan DiGiacomo
// Version: 1.0.0
//
// Defines engine rendering constants.
//
// Most will be derived from OpenGL and are redefined
// here for the sake of hypothetical portability to
// other platforms via preprocessor checks.
//
// Change platform: (doesn't do anyting)
// /DXXXX (2-4 character platform tag) [X360, X1, etc.]
// 

// NOTE: the following doesn't do anything, just in here because why not
// as such this is more or less empty and has no real meaning other than 
// includes
#if defined(X360)
// Xbox 360
// would use DX 9-10
#elif defined(X1)
// Xbox One
// would use DX 12
#elif defined(PS4)
// PS4
// would use GNM, GNMX, and PSSL
#elif defined(PS3)
// PS3
// would use OpenGL variant
#elif defined(MAC)
// Mac (OSX)
// would use OpenGL
#elif defined(WIN)
// Windows
// would use DX 12 
#else // DEFAULT (WINDOWS MACHINE)

// GLFW
#define GLFW_INCLUDE_GLU
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#endif
