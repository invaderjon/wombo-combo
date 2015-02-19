#include "Engine.h"

using namespace graphics;
using namespace std;

Engine::Engine()
{
	glfwCamera
}

Engine::~Engine()
{
}

int Engine::parseArgs(int argc, char** argv)
{
	// TODO: parse the arguments such as window size, full screen, etc.
	return SUCCESS;
}

int Engine::start(int argc, char** argv)
{
	// parses the args and checks the result
	int msg = parseArgs(argc, argv);
	if (msg != SUCCESS)
		return msg;

	// initializes GLFW
	msg = initGLFW();
	if (msg != SUCCESS)
		return msg;

	// adds input printer
	InputManager::getInstance()->addListener(new InputPrinter());

	// initializes OpenGL settings
	initGL();

	// waits until the window is closed
	loop();

	// destroys the window
	glfwDestroyWindow(window);

	// terminates GLFW
	glfwTerminate();

	// starts main loop
	return SUCCESS;
}

int Engine::initGLFW()
{
	if (!glfwInit())
		return EXIT_FAILURE;

	// sets the error callback method
	glfwSetErrorCallback(onErrorReceived);

	// creates the window
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	// if window failed terminate
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// defines the current context
	glfwMakeContextCurrent(window);

	// sets window callbacks
	glfwSetKeyCallback(window, InputManager::onKeyboardInput);
	glfwSetCursorEnterCallback(window, InputManager::onMouseEnter);
	glfwSetMouseButtonCallback(window, InputManager::onMouseButton);
	glfwSetCursorPosCallback(window, InputManager::onMouseMove);
	glfwSetScrollCallback(window, InputManager::onScroll);
	glfwSetDropCallback(window, InputManager::onFileDropped);

	// sets up rendering options
	glfwSwapInterval(1);

	return SUCCESS;
}

void Engine::initGL() {
	// enables depth test
	glEnable(GL_DEPTH_TEST);

	// sets depth test mode
	glDepthFunc(GL_LESS);
}

void Engine::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		measure();
		render();
		glfwPollEvents();
	}
}

void Engine::render()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(window);
}

void Engine::measure()
{
	// updates the frame size
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
}

void Engine::onErrorReceived(int error, const char* description)
{
	fputs(description, stderr);
}