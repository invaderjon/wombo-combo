#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;

// vertex vectors
in vec3 vInitPos;
in vec3 vInitVel;
in vec3 vAcc;
in float dAge;

// infos
varying vec3 gPosition;
varying vec3 gNormal;
varying vec3 position;
varying vec3 normal;

out vec3 lightPos;

void main()
{
	// calculates world space posiiton
	vec3 vPosition = vInitPos + vInitVel*dAge + 0.5*vAcc*dAge*dAge;
	vec4 pos = mView * mModel * vec4(vPosition, 1.0);
	vec4 gpos = mModel * vec4(vPosition, 1.0);
	vec4 light = mView * vec4(20.0, 20.0, 20.0, 1.0);

	// blinn-phong shading information
	gPosition = vec3(gpos) / gpos.w;
	gNormal = vec3(0,0,0);
	position = vec3(pos) / pos.w;
	normal = vec3(0,0,0);
	lightPos = vec3(light) / light.w;

	// calculates point size
	vec3 cam = vec3(mView[1][2], mView[2][2], mView[3][2]);
	float dist = length(vPosition - cam);

	gl_PointSize = 25.0f/dist;

	// camera space position
	gl_Position = mProjection * pos;
}