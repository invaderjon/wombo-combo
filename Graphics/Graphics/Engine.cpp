#include "Engine.h"

using namespace graphics;
using namespace std;

Engine::Engine()
{
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
	//InputManager::getInstance()->addListener(new InputPrinter());

	// initializes glew
	if (initGLEW() != GLEW_OK)
		throw runtime_error("GLEW failed to initialize!");

	// initializes OpenGL settings
	initGL();

	// sets up engine
	initEngine();

	// waits until the window is closed
	loop();

	// destroys the window
	glfwDestroyWindow(mWindow);

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
	mWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	// if window failed terminate
	if (!mWindow)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// defines the current context
	glfwMakeContextCurrent(mWindow);

	// sets window callbacks
	glfwSetKeyCallback(mWindow, InputManager::onKeyboardInput);
	glfwSetCursorEnterCallback(mWindow, InputManager::onMouseEnter);
	glfwSetMouseButtonCallback(mWindow, InputManager::onMouseButton);
	glfwSetCursorPosCallback(mWindow, InputManager::onMouseMove);
	glfwSetScrollCallback(mWindow, InputManager::onScroll);
	glfwSetDropCallback(mWindow, InputManager::onFileDropped);
	glfwSetWindowSizeCallback(mWindow, Engine::resize);
	glfwSetFramebufferSizeCallback(mWindow, Engine::onBufferResized);

	// sets up rendering options
	glfwSwapInterval(1);

	return SUCCESS;
}

GEenum Engine::initGLEW()
{
	return glewInit();
}

void Engine::initGL() {
	/////////////////////////////////
	// Shader Loading
	/////////////////////////////////

	// gets version info for shader proecessing
	GEint major;
	GEint minor;
	GEint version;
	GEint target;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	// displays version of pengl being used
	cout << "Running OpenGL Version " << glGetString(GL_VERSION) << endl;
	cout << "Major: " << major << "  Minor: " << minor << endl << endl;

	// determines if the the version is suitable and if it is which shader version to use
	version = major * 100 + minor * 10;
	
	// determines the target version
	// if its less than 3.3 than it can't be used
	if (version < 330)
		throw runtime_error("The version of OpenGL on this computer is unsupported.");
	else
		target = 330;

	// loads the shaders and program
	stringstream vert = stringstream();
	stringstream frag = stringstream();
	vert << "sh_vert_" << target << ".glsl";
	frag << "sh_frag_" << target << ".glsl";

	Shader shaders[2];
	shaders[0] = Shader(vert.str(), GL_VERTEX_SHADER);
	shaders[1] = Shader(frag.str(), GL_FRAGMENT_SHADER);

	// creates the new program
	Program program(&shaders[0], 2);
	glUseProgram(program.id());

	// releases the shaders
	shaders[0].release();
	shaders[1].release();

	/////////////////////////////////
	// Option Configuration
	/////////////////////////////////

	// enables depth test
	glEnable(GL_DEPTH_TEST);

	// sets depth test mode
	glDepthFunc(GL_LESS);

	// textures
	glEnable(GL_TEXTURE_2D);

	glClearColor(.5f, .5f, .5f, 1.0f);

	// gets attribute indices
	mIndices.attrs.position = glGetAttribLocation(program.id(), "vPosition");
	mIndices.attrs.normal = glGetAttribLocation(program.id(), "vNormal");

	// gets matrix indices
	mIndices.matrices.model = glGetUniformLocation(program.id(), "mModel");
	mIndices.matrices.view = glGetUniformLocation(program.id(), "mView");
	mIndices.matrices.projection = glGetUniformLocation(program.id(), "mProjection");
	mIndices.matrices.normal = glGetUniformLocation(program.id(), "mNormal");

	// gets texture indices
	mIndices.heightMap.grassUniform = glGetUniformLocation(program.id(), "grassTex");
	mIndices.heightMap.dirtUniform = glGetUniformLocation(program.id(), "dirtTex");
	mIndices.heightMap.rockUniform = glGetUniformLocation(program.id(), "rockTex");
	mIndices.heightMap.snowUniform = glGetUniformLocation(program.id(), "snowTex");
	glProgramUniform1i(program.id(), mIndices.heightMap.grassUniform, 0);
	glProgramUniform1i(program.id(), mIndices.heightMap.dirtUniform, 1);
	glProgramUniform1i(program.id(), mIndices.heightMap.rockUniform, 2);
	glProgramUniform1i(program.id(), mIndices.heightMap.snowUniform, 3);
	
	// sets up the material block
	/*mIndices.material.binding = 10000;
	mIndices.material.index = glGetUniformBlockIndex(program.id(), "MaterialBlock");
	mIndices.material.buffer = Buffers::nextBuffer();
	glUniformBlockBinding(program.id(), mIndices.material.index, mIndices.material.binding);
	glGenBuffers(1, &mIndices.material.buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, mIndices.material.buffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, mIndices.material.binding, mIndices.material.buffer);*/
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	
}

void Engine::initEngine()
{
	// gets the input manager
	mInputManager = InputManager::getInstance();

	// creates and registers the camera
	mCamera = new ArcBallCamera();
	mInputManager->addListener(mCamera);

	// test height map
	loadHeightMap();
}

void Engine::loadHeightMap()
{
	mHeightMap = new HeightMap("Textures/map.bmp");
	mHeightMap->push(mIndices.attrs);
}

void Engine::loop()
{

	chrono::time_point<chrono::high_resolution_clock> start, end;
	chrono::nanoseconds duration;
	long long diff;
	while (!glfwWindowShouldClose(mWindow))
	{
		start = chrono::high_resolution_clock::now();
		measure();
		update();
		render();
		glfwPollEvents();
		end = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
		diff = (TARGET_FRAME_TIME - duration.count());
		if (diff > 0) {
			Sleep(diff / 1000000);
		}
	}
}

void Engine::update()
{
	// updates the heightmap
	Mat4 view = mCamera->view();
	mHeightMap->update(&view);
}

void Engine::render()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniformMatrix4fv(mIndices.matrices.projection, 1, GL_FALSE, glm::value_ptr(mCamera->projection()));
	glUniformMatrix4fv(mIndices.matrices.view, 1, GL_FALSE, glm::value_ptr(mCamera->view()));


	// renders the heightmap
	mHeightMap->render(&mIndices);

	// draw
	glfwSwapBuffers(mWindow);
}

void Engine::resize(GLFWwindow* window, GEint width, GEint height)
{
}

void Engine::onBufferResized(GLFWwindow* window, GEint width, GEint height)
{
	glViewport(0, 0, width, height);
}

void Engine::measure()
{
	// updates the frame size
	glfwGetFramebufferSize(mWindow, &width, &height);
	mCamera->setSize(GEfloat(width), GEfloat(height));
	
}

void Engine::onErrorReceived(int error, const char* description)
{
	fputs(description, stderr);
}