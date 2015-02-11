#pragma once

//
// Title: Primitives
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

// NOTE: the following doesn't do anything, just thought it'd be cool to have
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
// MAC
// would use OpenGL
#else // DEFAULT
#include <GL\glut.h>
#endif
