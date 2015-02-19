#include "InputManager.h"

using namespace graphics;

InputManager* InputManager::sInstance = NULL;

// (de)constructors

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

// instance management function

InputManager* InputManager::getInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager;
	}
	return sInstance;
}

// callback functions

void InputManager::onKeyboardInput(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	InputManager* inst = getInstance();
	int keyMods;

	// calculates the mods
	if (mods & GLFW_MOD_SHIFT)
		keyMods |= MOD_SHIFT;
	else if (mods & GLFW_MOD_CONTROL)
		keyMods |= MOD_CTRL;
	else if (mods & GLFW_MOD_SUPER)
		keyMods |= MOD_CTRL;
	else if (mods & GLFW_MOD_ALT)
		keyMods |= MOD_ALT;
	mods = keyMods;

	// determines the action
	switch (action)
	{
	case GLFW_PRESS:				// key pressed
		action = INPUT_ACTION_PRESS;
		break;
	case GLFW_REPEAT:				// key held & repeat
		action = INPUT_ACTION_REPEAT;
		break;
	case GLFW_RELEASE:				// key released
	default:
		action = INPUT_ACTION_RELEASE;
		break;
	}

	// determines the key
	switch (key)
	{
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		key = KEY_UP;
		break;
	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		key = KEY_DOWN;
		break;
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		key = KEY_LEFT;
		break;
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		key = KEY_RIGHT;
		break;
	case GLFW_KEY_ENTER:
		key = KEY_CONFIRM;
		break;
	case GLFW_KEY_ESCAPE:
		key = KEY_CANCEL;
		break;
	default:
		key = KEY_UNKNOWN;
		break;
	}

	// notifies the listeners
	inst->onInput(key, action, mods);
}

void InputManager::onMouseEnter(GLFWwindow* window, int entered)
{
	// TODO: react
}

void InputManager::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* inst = getInstance();
	int keyMods = 0;

	// determines the action
	switch (action)
	{
	case GLFW_PRESS:				// key pressed
		action = INPUT_ACTION_PRESS;
		break;
	case GLFW_REPEAT:				// key held & repeat
		action = INPUT_ACTION_REPEAT;
		break;
	case GLFW_RELEASE:				// key released
	default:
		action = INPUT_ACTION_RELEASE;
		break;
	}

	// calculates the mods
	if (mods & GLFW_MOD_SHIFT)
		keyMods |= MOD_SHIFT;
	else if (mods & GLFW_MOD_CONTROL)
		keyMods |= MOD_CTRL;
	else if (mods & GLFW_MOD_SUPER)
		keyMods |= MOD_CTRL;
	else if (mods & GLFW_MOD_ALT)
		keyMods |= MOD_ALT;
	mods = keyMods;

	// TODO: react
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT: // 1
		button = MOUSE_LEFT;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT: // 2
		button = MOUSE_RIGHT;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE: // 3
		button = MOUSE_MIDDLE;
		break;
	case GLFW_MOUSE_BUTTON_4:
	case GLFW_MOUSE_BUTTON_5:
	case GLFW_MOUSE_BUTTON_6:
	case GLFW_MOUSE_BUTTON_7:
	case GLFW_MOUSE_BUTTON_8:
	default:
		break;
	}

	// notifies the listeners
	inst->onClick(button, action, mods);
}

void InputManager::onMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	// gets instance
	InputManager* inst = getInstance();
	
	// wraps info in cursor
	Cursor curs(xpos, ypos);
	
	// notifies listeners
	inst->onCursorMove(curs);
}

void InputManager::onScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	// notifies listeners
	getInstance()->onScroll(xoffset, yoffset);
}

void InputManager::onFileDropped(GLFWwindow* window, int count, const char** names)
{
	// TODO: react
}

// listener management functions

void InputManager::addListener(IControllable* listener)
{
	if (listener == NULL)
		return;
	mMtx.lock();
	mListeners.push_back(listener);
	mMtx.unlock();
}

void InputManager::removeListener(IControllable* listener)
{
	if (listener == NULL)
		return;
	mMtx.lock();
	mListeners.remove(listener);
	mMtx.unlock();
}

// calls to notify all listeners

void InputManager::onCursorMove(Cursor cursor)
{
	mMtx.lock();
	list<IControllable*>::iterator iter;
	for (iter = mListeners.begin(); iter != mListeners.end(); iter++)
		(*iter)->onCursorMove(cursor);
	mMtx.unlock();
}

void InputManager::onInput(int key, int action, int mods)
{
	mMtx.lock();
	list<IControllable*>::iterator iter;
	for (iter = mListeners.begin(); iter != mListeners.end(); iter++)
		(*iter)->onInput(key, action, mods);
	mMtx.unlock();
}

void InputManager::onClick(int button, int action, int mods)
{
	mMtx.lock();
	list<IControllable*>::iterator iter;
	for (iter = mListeners.begin(); iter != mListeners.end(); iter++)
		(*iter)->onClick(button, action, mods);
	mMtx.unlock();
}

void InputManager::onScroll(double xoffset, double yoffset)
{
	mMtx.lock();
	list<IControllable*>::iterator iter;
	for (iter = mListeners.begin(); iter != mListeners.end(); iter++)
		(*iter)->onScroll(xoffset, yoffset);
	mMtx.unlock();
}