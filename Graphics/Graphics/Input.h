#pragma once

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3

#define KEY_UNKNOWN -1
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_CONFIRM 5
#define KEY_SELECT KEY_CONFIRM
#define KEY_CANCEL 6
#define KEY_SPACE 7

#define INPUT_ACTION_RELEASE 0
#define INPUT_ACTION_PRESS 1
#define INPUT_ACTION_REPEAT 2

#define MOD_LSHIFT 0x0001
#define MOD_RSHIFT 0x0002
#define MOD_SHIFT 0x0003
#define MOD_LCTRL 0x0004
#define MOD_RCTRL 0x0008
#define MOD_CTRL 0x000C
#define MOD_LALT 0x0010
#define MOD_RALT 0x0020
#define MOD_ALT 0x0030

namespace graphics
{
	typedef struct	sCursor
	{
		double		x;
		double		y;

		// constructor
		sCursor() : x(0.0), y(0.0) { }
		sCursor(double X, double Y) : x(X), y(Y) { }
	}				Cursor;
}