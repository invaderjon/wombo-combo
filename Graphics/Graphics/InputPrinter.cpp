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
	case MOUSE_LEFT:
		sButton = "left button";
		break;
	case MOUSE_RIGHT:
		sButton = "right button";
		break;
	case MOUSE_MIDDLE:
		sButton = "middle button";
		break;
	default:
		sButton = "unknown button";
		break;
	}

	// determines the action
	switch (action)
	{
	case INPUT_ACTION_PRESS:
		sAction = "pressed";
		break;
	case INPUT_ACTION_RELEASE:
		sAction = "released";
		break;
	case INPUT_ACTION_REPEAT:
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
	case KEY_UP:
		sKey = "UP";
		break;
	case KEY_DOWN:
		sKey = "DOWN";
		break;
	case KEY_LEFT:
		sKey = "LEFT";
		break;
	case KEY_RIGHT:
		sKey = "RIGHT";
		break;
	case KEY_CONFIRM:
		sKey = "CONFIRM/SELECT";
		break;
	case KEY_CANCEL:
		sKey = "CANCEL";
		break;
	case KEY_SPACE:
		sKey = "SPACE";
		break;
	case KEY_UNKNOWN:
	default:
		sKey = "UNKNOWN";
		break;
	}

	// determines the action
	switch (action)
	{
	case INPUT_ACTION_PRESS:
		sAction = "pressed";
		break;
	case INPUT_ACTION_RELEASE:
		sAction = "released";
		break;
	case INPUT_ACTION_REPEAT:
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