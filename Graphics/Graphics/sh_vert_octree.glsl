#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

// vertex vectors
in vec3 vPosition;

void main()
{
	// camera space position
	gl_Position = mProjection * mView * mModel * vec4(vPosition, 1.0);
}