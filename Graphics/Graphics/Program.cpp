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
	extractResources(GE_PROGRAM_INTROSPECTION_INPUTS);
	extractResources(GE_PROGRAM_INTROSPECTION_UNIFORMS);
	extractResources(GE_PROGRAM_INTROSPECTION_UNIFORM_BLOCKS);
}

void Program::extractResources(GEenum type)
{
	GEint count;
	glUseProgram(mId);
	// TODO: make if statement preprocessor (can't at the moment because the glew attribute can't be preprocessor)
	///////////////////////////////////////////////////////////////////////
	////////////////////////// ARB WAY (NEW WAY) //////////////////////////
	///////////////////////////////////////////////////////////////////////
	if (GLEW_ARB_program_interface_query)
	{
		// determine type
		switch (type)
		{
		case GE_PROGRAM_INTROSPECTION_INPUTS:
			type = GL_PROGRAM_INPUT;
			break;
		case GE_PROGRAM_INTROSPECTION_UNIFORMS:
			type = GL_UNIFORM;
			break;
		case GE_PROGRAM_INTROSPECTION_UNIFORM_BLOCKS:
			type = GL_UNIFORM_BLOCK;
			break;
		default: type = -1;
		}

		// perform introspection
		vector<GEchar> nameData;
		vector<GEenum> props;
		props.push_back(GL_NAME_LENGTH);
		props.push_back(GL_TYPE);
		props.push_back(GL_ARRAY_SIZE);
		if (type != GL_UNIFORM_BLOCK)
			props.push_back(GL_LOCATION);
		else
			props.push_back(GL_BUFFER_DATA_SIZE);
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
			{
				location = glGetUniformBlockIndex(mId, name.c_str());
				// creates and inserts a new uniform block
				mUniformBlocks.insert(make_pair(name, UniformBlock(mId, name, location)));
			}

			printf("Inserting: %s:%i\n", name.c_str(), location);
			mResources.insert(std::make_pair(name, location));
		}
	}
	///////////////////////////////////////////////////////////////////////
	//////////////////////// NON ARB WAY (OLD WAY) ////////////////////////
	///////////////////////////////////////////////////////////////////////
	else 
	{
		// determine type
		GEint maxNameLengthQuery;
		switch (type)
		{
		case GE_PROGRAM_INTROSPECTION_INPUTS:
			type = GL_ACTIVE_ATTRIBUTES;
			maxNameLengthQuery = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH;
			break;
		case GE_PROGRAM_INTROSPECTION_UNIFORMS:
			type = GL_ACTIVE_UNIFORMS;
			maxNameLengthQuery = GL_ACTIVE_UNIFORM_MAX_LENGTH;
			break;
		case GE_PROGRAM_INTROSPECTION_UNIFORM_BLOCKS:
			type = GL_ACTIVE_UNIFORM_BLOCKS;
			maxNameLengthQuery = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH;
			break;
		default:
			type = -1;
			
		}

		// gets the number of the given type and name max length
		GEint maxNameLength;
		glGetProgramiv(mId, type, &count);
		glGetProgramiv(mId, maxNameLengthQuery, &maxNameLength);
		if (maxNameLength <= 0) // apparently this can be buggy on some drivers
			maxNameLength = 256;

		// creates variables for storing temp info
		GEint i;
		GEint arrSize = 0;
		GEint len = 0;
		GEint location;
		GEenum varType = 0;
		vector<GEchar> nameData(maxNameLength);

		// gets more info depending on type
		switch (type)
		{
		case GL_ACTIVE_ATTRIBUTES:
			for (i = 0; i < count; ++i, arrSize = 0, varType = 0, len = 0)
			{
				// gets data
				glGetActiveAttrib(mId, i, nameData.size(), &len, &arrSize, &varType, &nameData[0]);
				
				// if a name was found (was a valid active attribute)
				if (len > 0)
				{
					string name((char*)&nameData[0], len);
					location = glGetAttribLocation(mId, name.c_str());
					
					// prints debuing info and adds to list
					printf("Inserting: %s:%i\n", name.c_str(), location);
					mResources.insert(std::make_pair(name, location));
				}
			}
			break;
		case GL_ACTIVE_UNIFORMS:
			for (i = 0; i < count; ++i, arrSize = 0, varType = 0, len = 0)
			{
				// gets data
				glGetActiveUniform(mId, i, nameData.size(), &len, &arrSize, &varType, &nameData[0]);

				// if a name was actualy found (was a valid active uniform)
				if (len > 0)
				{
					string name((char*)&nameData[0], len);
					location = glGetUniformLocation(mId, name.c_str());

					// prints debuing info and adds to list
					printf("Inserting: %s:%i\n", name.c_str(), location);
					mResources.insert(std::make_pair(name, location));
				}
			}
			break;
		case GL_ACTIVE_UNIFORM_BLOCKS:
			for (i = 0; i < count; ++i)
			{
				// gets data
				glGetActiveUniformBlockName(mId, i, nameData.size(), &len, &nameData[0]);


				// if a name was actualy found (was a valid active uniform block)
				if (len > 0)
				{
					string name((char*)&nameData[0], len);
					location = glGetUniformBlockIndex(mId, name.c_str());

					// creates and inserts a new uniform block
					mUniformBlocks.insert(make_pair(name, UniformBlock(mId, name, location)));

					// prints debuing info and adds to list
					printf("Inserting: %s:%i\n", name.c_str(), location);
					mResources.insert(std::make_pair(name, location));
				}
			}
			break;
		}
	}
}