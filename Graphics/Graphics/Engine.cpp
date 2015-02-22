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

	// gets attribute indices
	mIndices.attrs.position = glGetAttribLocation(program.id(), "vPosition");
	mIndices.attrs.normal = glGetAttribLocation(program.id(), "vNormal");

	// gets matrix indices
	mIndices.matrices.model = glGetUniformLocation(program.id(), "mModel");
	mIndices.matrices.view = glGetUniformLocation(program.id(), "mView");
	mIndices.matrices.projection = glGetUniformLocation(program.id(), "mProjection");
	mIndices.matrices.normal = glGetUniformLocation(program.id(), "mNormal");

	// sets up the material block
	GEuint block = glGetUniformBlockIndex(program.id(), "Material");
	glUniformBlockBinding(program.id(), block, mIndices.material.binding);
	
	// creates buffer for material block
	mIndices.material.buffer = Buffers::nextBuffer();
	glGenBuffers(1, &mIndices.material.buffer);
	glBindBuffer(GL_UNIFORM_BUFFER, mIndices.material.buffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, mIndices.material.binding, mIndices.material.buffer);
}

void Engine::initEngine()
{
	// gets the input manager
	mInputManager = InputManager::getInstance();

	// creates and registers the camera
	mCamera = new ArcBallCamera();
	mInputManager->addListener(mCamera);

	// test drawing
	vao = 69;
	test = 42;

	// test vetex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	data = new Vert[3];
	data[0] = Vert(Vec4(-0.6f, -0.4f, 0.f, 1.0f), Vec3(0.0f, 0.0f, 1.0f));
	data[1] = Vert(Vec4(0.6f, -0.4f, 0.f, 1.0f), Vec3(0.0f, 0.0f, 1.0f));
	data[2] = Vert(Vec4(0.f, 0.6f, 0.f, 1.0f), Vec3(0.0f, 0.0f, 1.0f));

	// creates buffers
	glGenBuffers(1, &test);
	glBindBuffer(GL_ARRAY_BUFFER, test);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vert), data, GL_STATIC_DRAW);

	// sets attributes
	glVertexAttribPointer(mIndices.attrs.position, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(mIndices.attrs.normal, 3, GL_FLOAT, GL_TRUE, sizeof(Vert), (void*)(4 * sizeof(GEfloat)));

	// enables attributes
	glEnableVertexAttribArray(mIndices.attrs.position);
	glEnableVertexAttribArray(mIndices.attrs.normal);

	// unbinds vao
	glBindVertexArray(0);

	// test height map
	loadHeightMap();
}

void Engine::loadHeightMap()
{
	mHeightMap = new HeightMap("map.bmp", .1f);
	mHeightMap->push(mIndices.attrs);
}

void Engine::loop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		measure();
		update();
		render();
		glfwPollEvents();
	}
}

void Engine::update()
{
	Mat4 view = mCamera->view();

	// updates global matrices
	glUniformMatrix4fv(mIndices.matrices.projection, 1, GL_FALSE, glm::value_ptr(mCamera->projection()));
	glUniformMatrix4fv(mIndices.matrices.view, 1, GL_FALSE, glm::value_ptr(view));

	// updates the heightmap
	mHeightMap->update(&view);
}

void Engine::render()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// renders the heightmap
	mHeightMap->render(&mIndices);
	
	// test draw
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glfwSwapBuffers(mWindow);
}

void Engine::measure()
{
	// updates the frame size
	glfwGetFramebufferSize(mWindow, &width, &height);
	ratio = width / (float)height;
	mCamera->setSize(width, height);
}

void Engine::onErrorReceived(int error, const char* description)
{
	fputs(description, stderr);
}