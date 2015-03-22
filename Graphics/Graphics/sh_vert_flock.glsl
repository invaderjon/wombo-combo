#version 330

// matrices
uniform mat4 mView;
uniform mat4 mProjection;
in mat4 mInstModel;
in mat4 mInstNormal;

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
	vec4 pos = mView * mInstModel * vec4(vPosition, 1.0);
	vec4 gpos = mInstModel * vec4(vPosition, 1.0);
	vec4 light = mView * vec4(20.0, 20.0, 20.0, 1.0);

	// blinn-phong shading information
	mat3 norm = mat3(mInstNormal);
	gPosition = vec3(gpos) / gpos.w;
	gNormal = vNormal;
	position = vec3(pos) / pos.w;
	normal = normalize(norm * vNormal);
	lightPos = vec3(light) / light.w;

	// camera space position
	gl_Position = mProjection * pos;
}