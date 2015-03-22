#version 330

varying vec3 gPosition; // before transforms
varying vec3 gNormal;	// before transforms
varying vec3 position;  // after transforms
varying vec3 normal;

in vec3 lightPos;

const float PI = 3.1415926535897932384626433832795;
const float PI2 = PI/2.0f;

void main()
{
	// light info
	vec3 N = normalize(normal);
	vec3 L = normalize(lightPos - gPosition);
	float lambert = max(dot(L, N), 0.0);
	float spec = 0.0;
	
	// hard coded values due to broken material block
	vec3 diffuse = vec3(.9, .2, .2); // constant color
	vec3 ambient = vec3(.05, .05, .05);
	vec3 specular = vec3(.4, .4, .4);
	float shininess = 0.25f;

	// if there's specular, calculate it
	if (lambert > 0.0)
	{
		// determine eye position
		vec3 E = normalize(-position);

		// blinn-phong
		vec3 H = normalize(L + E);
		float specAngle = max(dot(H, N), 0.0);
		spec = pow(specAngle, shininess);
	}

	// caculate final color
	gl_FragColor = vec4(lambert * diffuse + spec * specular + ambient, 1.0);
}