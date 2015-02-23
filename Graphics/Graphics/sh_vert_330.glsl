#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform mat3 mNormal;

// vertex vectors
in vec3 vPosition;
in vec3 vNormal;

out vec3 normal;
out vec3 eye;

void main()
{
	mat4 viewModel = mView * mModel;
	vec4 pos = vec4(vPosition, 1.0);
	normal = normalize(mNormal * vNormal);
	vec4 e = -(viewModel * pos);
	eye = vec3(e.x, e.y, e.z);

	gl_Position = mProjection * pos;
}