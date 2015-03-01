#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform mat3 mNormal;

// vertex vectors
in vec3 vPosition;
in vec3 vNormal;

// infos
varying vec3 gPosition;
varying vec3 gNormal;
varying vec3 position;
varying vec3 normal;

out vec3 lightPos;

void main()
{
	// calculates world space posiiton
	vec4 pos = mView * mModel * vec4(vPosition, 1.0);
	vec4 gpos = mModel * vec4(vPosition, 1.0);
	vec4 light = mView * vec4(20.0, 20.0, 20.0, 1.0);

	// blinn-phong shading information
	gPosition = vec3(gpos) / gpos.w;
	gNormal = vNormal;
	position = vec3(pos) / pos.w;
	normal = normalize(mNormal * vNormal);
	lightPos = vec3(light) / light.w;

	// camera space position
	gl_Position = mProjection * pos;
}