#version 330

layout (std140) uniform Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess;
};

in vec3 normal;
in vec3 eye;

void main()
{
	// set specular to black
	vec3 spec = vec3(0.0);

	// normalize both input vectors
	vec3 n = normalize(normal);
	vec3 e = normalize(eye);
	vec3 l_dir = vec3(0, -1, -1);
	vec3 ambient = vec3(.05, .05, .05);
	vec3 specular = vec3(1, 1, 1);
	float shininess = .05;
	vec3 diffuse = vec3(.7, .7, .7);

	// calculates the light intensity
	float intensity = max(dot(n, -l_dir), 0.0);

	// if lit compute specular
	if (intensity > 0.0)
	{
		// compute half vector
		vec3 h = normalize(l_dir + e);

		// compute specular
		float intSpec = max(dot(h, n), 0.0);
		spec = specular * pow(intSpec, 1.0-shininess);
	}

	// sets the color
	gl_FragColor = vec4(max(diffuse * intensity + spec, ambient), 1.0);
}