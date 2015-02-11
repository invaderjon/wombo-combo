#include "Manager.h"

using namespace graphics;
using namespace std;

Manager::Manager()
{
}


Manager::~Manager()
{
}

void Manager::init(int argc, char** argv)
{
	glutInit(&argc, argv);

	// load resources
}

int Manager::start(const char* title)
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow(title);
	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutIdleFunc(&idle);
	glutKeyboardFunc(&keyboard);
	glutMouseFunc(&mouse);
	glutPassiveMotionFunc(&motion);
	
	// initializes glew
	glewInit();
	if (!GLEW_VERSION_2_0) {
		fprintf(stderr, "OpenGL 2.0 not available\n");
		return 1;
	}

	glutMainLoop();
	return 0;
}

void graphics::display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void graphics::idle()
{
	glutPostRedisplay();
}

void graphics::reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void graphics::keyboard(unsigned char key, int x, int y)
{
	// keyboard clicks
}

void graphics::mouse(int button, int state, int x, int y)
{
	// mouse clicks
}

void graphics::motion(int x, int y)
{
	// mouse motion
}