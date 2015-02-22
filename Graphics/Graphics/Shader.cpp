#include "Shader.h"

using namespace graphics;

/// <summary>
/// Creates an invalid shader.
/// </summary>
Shader::Shader()
{
	mId = -1;
}

/// <summary>
/// Loads and compiles a shader from a given file.
/// </summary>
/// <param name="path">The shader file path.</param>
/// <param name="type">The shader type.</param>
Shader::Shader(string path, GEint type)
{
	// creates the handle
	GEuint handle = glCreateShader(type);

	// load the code from file to the string
	string code = loadFile(path);
	const GEchar* src = code.c_str();
	
	// determines type name
	string typeName;
	switch (type)
	{
	case GL_VERTEX_SHADER:
		typeName = "vertex";
		break;
	case GL_FRAGMENT_SHADER:
		typeName = "fragment";
		break;
	case GL_GEOMETRY_SHADER:
		typeName = "geometry";
		break;
	case GL_TESS_CONTROL_SHADER:
		typeName = "tesselation control";
		break;
	case GL_TESS_EVALUATION_SHADER:
		typeName = "tesselation evaluation";
		break;
	case GL_COMPUTE_SHADER:
		typeName = "compute";
		break;
	default:
		typeName = "unknown";
		break;
	}

	// compiles shader
	cout << "Compiling " << typeName << " shader (file: " << path << ")." << endl;
	glShaderSource(handle, 1, &src, NULL);
	glCompileShader(handle);

	// checks compilation
	GEint result = GL_FALSE;
	GEint logLength;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
		vector<GEchar> shaderError((logLength > 1) ? logLength : 1);
		glGetShaderInfoLog(handle, logLength, NULL, &shaderError[0]);
		cout << &shaderError[0] << endl;

		glDeleteShader(handle);
		mId = -1;
		return;
	}

	// saves the id
	mId = handle;
}

Shader::~Shader()
{
}

GEuint Shader::id() const
{
	return mId;
}

/// <summary>
/// Releases the gl side shader resources.
/// </summary>
void Shader::release()
{
	glDeleteShader(mId);
}

/// <summary>
/// Loads a file at the specified path.
/// </summary>
/// <param name="path">The file path.</param>
/// <returns>The file content.</returns>
string Shader::loadFile(string path)
{
	// ensures the path isn't empty
	assert(!path.empty());

	// set up variables
	stringstream content = stringstream();
	ifstream fs(path, ios::in);

	// ensures the file exists
	if (!fs.is_open())
	{
		cerr << "Could not read file " << path << ". File does not exist." << endl;
		return "";
	}

	// reads the file
	string line = "";
	while (!fs.eof())
	{
		getline(fs, line);
		content << line << "\n";
	}

	// returns the file content
	return content.str();
}