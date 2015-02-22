#include "Program.h"

using namespace graphics;

Program::Program(Shader* shaders, GEuint count)
{
	GEuint i;
	
	// creates the program
	GEuint program = glCreateProgram();

	// attaches the shaders
	for (i = 0; i < count; i++)
		glAttachShader(program, shaders[i].id());

	// links the program
	glLinkProgram(program);

	// checks result
	GEint result = GL_FALSE;
	GEint logLength;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		vector<GEchar> programError((logLength > 1) ? logLength : 1);
		glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
		cout << &programError[0] << endl;
		
		// delete the program
		glDeleteProgram(program);
		mId = -1;
		return;
	}

	// stores the program id
	mId = program;

	// detaches shaders
	for (i = 0; i < count; i++)
		glDetachShader(program, shaders[i].id());
}


Program::~Program()
{
}

GEuint Program::id() const
{
	return mId;
}