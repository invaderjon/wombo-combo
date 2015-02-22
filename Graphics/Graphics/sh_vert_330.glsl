#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform mat3 mNormal;

// vertex vectors
in vec4 vPosition;
in vec3 vNormal;

out vec3 normal;
out vec3 eye;

void main()
{
	mat4 viewModel = mView * mModel;
	normal = normalize(mNormal * vNormal);
	eye = -(viewModel * vPosition);

	gl_Position = mProjection * mView * mModel * vPosition;
}