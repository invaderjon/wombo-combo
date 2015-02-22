#version 330

layout (std140) uniform Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess;
};

layout (std140) uniform Lights {
	vec3 l_dir;
};

in vec3 normal;
in vec3 eye;

out vec4 color;

void main()
{
	// set specular to black
	vec3 spec = vec3(0.0);

	// normalize both input vectors
	vec3 n = normalize(normal);
	vec3 e = normalize(eye);

	// calculates the light intensity
	float intensity = max(dot(n, l_dir), 0.0);

	// if lit compute specular
	if (intensity > 0.0)
	{
		// compute half vector
		vec3 h = normalize(l_dir + e);

		// compute specular
		float intSpec = max(dot(h, n), 0.0);
		spec = specular * pow(intSpec, shininess);
	}

	// sets the color
	color = vec4(1.0, 0.0, 0.0, 1.0);//vec4(max(diffuse * intensity + spec, ambient), 1.0);
}