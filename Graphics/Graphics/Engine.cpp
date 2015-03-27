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
	// Option Configuration
	/////////////////////////////////

	// enables depth test
	glEnable(GL_DEPTH_TEST);

	// sets depth test mode
	glDepthFunc(GL_LESS);

	// textures
	glEnable(GL_TEXTURE_2D);

	glClearColor(.5f, .5f, .5f, 1.0f);

	/////////////////////////////////
	// Shader Loading
	/////////////////////////////////

	// gets version info for shader proecessing
	GEint version;
	GEint major;
	GEint minor;
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
	mHMProgram = new Program(&shaders[0], 2);

	// releases the shaders
	shaders[0].release();
	shaders[1].release();

	// creates oct tree program
	shaders[0] = Shader("sh_vert_octree.glsl", GL_VERTEX_SHADER);
	shaders[1] = Shader("sh_frag_octree.glsl", GL_FRAGMENT_SHADER);

	// creates oct tree program
	mOTProgram = new Program(&shaders[0], 2);

	//creates flock program
	shaders[0] = Shader("sh_vert_flock.glsl", GL_VERTEX_SHADER);
	shaders[1] = Shader("sh_frag_flock.glsl", GL_FRAGMENT_SHADER);
	
	//creates flock program
	mFProgram = new Program(&shaders[0], 2);

	// release the shaders
	shaders[0].release();
	shaders[1].release();

	// starts off with the height map
	glUseProgram(mHMProgram->id());
	
	/////////////////////////////////
	// Program Configuration
	/////////////////////////////////

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

	// test flocking
	loadFlock();
}

void Engine::loadHeightMap()
{
	glUseProgram(mHMProgram->id());
	mHeightMap = new HeightMap("Resources/textures/heightmap/map.bmp");
	mHeightMap->push(mHMProgram);

	glUseProgram(mOTProgram->id());
	mOctree = new Octree(&mHeightMap->mVertices[0], &mHeightMap->mFaces[0], mHeightMap->mFaces.size());
	mOctree->push(mOTProgram);
}

void Engine::loadFlock()
{
	glUseProgram(mFProgram->id());
	mFlock = new Flock(250, 10.0f);
	mFlock->push(mFProgram);
}

void Engine::loop()
{

	chrono::time_point<chrono::high_resolution_clock> start, end;
	chrono::nanoseconds duration;
	long long diff = 0;
	while (!glfwWindowShouldClose(mWindow))
	{
		start = chrono::high_resolution_clock::now();
		measure();
		update(diff / 1000000000.0f);
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

void Engine::update(GEdouble elapsed)
{
	// updates the heightmap
	Mat4 view = mCamera->view();
	mHeightMap->update(&view, elapsed);
	mFlock->update(&view, elapsed);
}

void Engine::render()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// heightmap
	glUseProgram(mHMProgram->id());
	glUniformMatrix4fv(mHMProgram->resource(MAT_PROJECTION), 1, GL_FALSE, glm::value_ptr(mCamera->projection()));
	glUniformMatrix4fv(mHMProgram->resource(MAT_VIEW), 1, GL_FALSE, glm::value_ptr(mCamera->view()));


	// renders the heightmap
	mHeightMap->render(mHMProgram);

	// octree
	glUseProgram(mOTProgram->id());
	glUniformMatrix4fv(mOTProgram->resource(MAT_PROJECTION), 1, GL_FALSE, glm::value_ptr(mCamera->projection()));
	glUniformMatrix4fv(mOTProgram->resource(MAT_VIEW), 1, GL_FALSE, glm::value_ptr(mCamera->view()));

	// renders the octree
	mOctree->render(mOTProgram);

	glUseProgram(mFProgram->id());
	glUniformMatrix4fv(mFProgram->resource(MAT_PROJECTION), 1, GL_FALSE, glm::value_ptr(mCamera->projection()));
	glUniformMatrix4fv(mFProgram->resource(MAT_VIEW), 1, GL_FALSE, glm::value_ptr(mCamera->view()));

	mFlock->render(mFProgram);

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