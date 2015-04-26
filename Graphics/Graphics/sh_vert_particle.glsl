#version 330

// matrices
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mProjection;
uniform mat3 mNormal;

// vertex vectors
in vec3 vPosition;
in vec3 vInstPos;
in vec4 vInstCol;
in float vInstSize;

// output uv
varying vec2 uv;
varying vec4 vColor;

// texture
void main()
{
	// calcultes uv
	//uv = vec2(vPosition.x + 0.5, vPosition.y + 0.5);  

	// extracts camera space
	vec3 camRight = normalize(vec3(mView[0][0], mView[1][0], mView[2][0]));
	vec3 camUp = normalize(vec3(mView[0][1], mView[1][1], mView[2][1]));

	// calculates billboarded position
	vec4 pos = vec4(vInstPos + camUp*(vPosition.y*vInstSize) + camRight*(vPosition.x*vInstSize), 1.0);
	
	// calcultes uv
	uv = vec2(vPosition.x + 0.5, vPosition.y + 0.5);

	vColor = vInstCol;
	
	// camera space position
	gl_Position = mProjection * mView * pos;
}