#include "InputPrinter.h"

using namespace graphics;

InputPrinter::InputPrinter()
{
}

InputPrinter::~InputPrinter()
{
}

void InputPrinter::onCursorMove(Cursor cursor)
{
	cout << "Cursor: x: " << cursor.x << "  y: " << cursor.y << endl;
}

void InputPrinter::onClick(int button, int action, int mods)
{
	char* sButton;
	char* sAction;

	// determines the button
	switch (button)
	{
	case GE_MOUSE_LEFT:
		sButton = "left button";
		break;
	case GE_MOUSE_RIGHT:
		sButton = "right button";
		break;
	case GE_MOUSE_MIDDLE:
		sButton = "middle button";
		break;
	default:
		sButton = "unknown button";
		break;
	}

	// determines the action
	switch (action)
	{
	case GE_INPUT_ACTION_PRESS:
		sAction = "pressed";
		break;
	case GE_INPUT_ACTION_RELEASE:
		sAction = "released";
		break;
	case GE_INPUT_ACTION_REPEAT:
		sAction = "being held";
		break;
	default:
		sAction = "doing something...";
		break;
	}

	cout << "Mouse: " << sButton << " is " << sAction << endl;
}

void InputPrinter::onInput(int key, int action, int mods)
{
	char* sKey;
	char* sAction;

	// determines the key being updated
	switch (key)
	{
	case GE_KEY_UP:
		sKey = "UP";
		break;
	case GE_KEY_DOWN:
		sKey = "DOWN";
		break;
	case GE_KEY_LEFT:
		sKey = "LEFT";
		break;
	case GE_KEY_RIGHT:
		sKey = "RIGHT";
		break;
	case GE_KEY_CONFIRM:
		sKey = "CONFIRM/SELECT";
		break;
	case GE_KEY_CANCEL:
		sKey = "CANCEL";
		break;
	case GE_KEY_SPACE:
		sKey = "SPACE";
		break;
	case GE_KEY_UNKNOWN:
	default:
		sKey = "UNKNOWN";
		break;
	}

	// determines the action
	switch (action)
	{
	case GE_INPUT_ACTION_PRESS:
		sAction = "pressed";
		break;
	case GE_INPUT_ACTION_RELEASE:
		sAction = "released";
		break;
	case GE_INPUT_ACTION_REPEAT:
		sAction = "being held";
		break;
	default:
		sAction = "doing something...";
		break;
	}

	cout << "Key: " << sKey << " is " << sAction << endl;
}

void InputPrinter::onScroll(double xoffset, double yoffset)
{
	cout << "Scroll: x: " << xoffset << " y: " << yoffset << endl;
}