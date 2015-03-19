#include "Program.h"

using namespace graphics;

Program::Program(Shader* shaders, GEuint count)
	: mResources()
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

	// extracts attributes, uniforms, etc.
	extract();
}

Program::~Program()
{
}

GEuint Program::id() const
{
	return mId;
}

GEint Program::resource(const string& name) const
{
	return mResources.at(name);
}

void Program::extract()
{
	extractResources(GL_PROGRAM_INPUT);
	extractResources(GL_UNIFORM);
	extractResources(GL_UNIFORM_BLOCK);
}

void Program::extractResources(GEenum type)
{
	GEint count;
	glUseProgram(mId);

	#ifdef GL_ARB_INTERFACE
	vector<GEchar> nameData;
	vector<GEenum> props;
	props.push_back(GL_NAME_LENGTH);
	props.push_back(GL_TYPE);
	props.push_back(GL_ARRAY_SIZE);
	if (type != GL_UNIFORM_BLOCK)
		props.push_back(GL_LOCATION);
	vector<GEint> values(props.size());

	glGetProgramInterfaceiv(mId, type, GL_ACTIVE_RESOURCES, &count);

	// look up info for each
	for (int attrib = 0; attrib < count; ++attrib)
	{
		glGetProgramResourceiv(mId, type, attrib, props.size(), &props[0],
			values.size(), NULL, &values[0]);
		nameData.resize(values[0]);
		glGetProgramResourceName(mId, type, attrib, nameData.size(), NULL, &nameData[0]);
		
		// the name
		string name((char*)&nameData[0], nameData.size() - 1);

		// determines the location/index
		GEint location = 0;
		if (type != GL_UNIFORM_BLOCK)
			location = values[3];
		else
			location = glGetUniformBlockIndex(mId, name.c_str());

		printf("Inserting: %s:%i\n", name.c_str(), location);
		mResources.insert(std::make_pair(name, location));
	}
	#else
	// non arb way
	#endif
	
}