#pragma once

#include <glm/glm.hpp>

#define GE_MOUSE_LEFT 1
#define GE_MOUSE_RIGHT 2
#define GE_MOUSE_MIDDLE 3

#define GE_KEY_UNKNOWN -1
#define GE_KEY_UP 1
#define GE_KEY_DOWN 2
#define GE_KEY_LEFT 3
#define GE_KEY_RIGHT 4
#define GE_KEY_CONFIRM 5
#define GE_KEY_SELECT KEY_CONFIRM
#define GE_KEY_CANCEL 6
#define GE_KEY_SPACE 7

#define GE_INPUT_ACTION_RELEASE 0
#define GE_INPUT_ACTION_PRESS 1
#define GE_INPUT_ACTION_REPEAT 2

#define GE_MOD_LSHIFT 0x0001
#define GE_MOD_RSHIFT 0x0002
#define GE_MOD_SHIFT 0x0003
#define GE_MOD_LCTRL 0x0004
#define GE_MOD_RCTRL 0x0008
#define GE_MOD_CTRL 0x000C
#define GE_MOD_LALT 0x0010
#define GE_MOD_RALT 0x0020
#define GE_MOD_ALT 0x0030

namespace graphics
{
	typedef glm::vec2 Cursor;
}