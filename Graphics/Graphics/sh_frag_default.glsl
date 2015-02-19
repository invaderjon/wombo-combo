#version 450

layout (std140) uniform Material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float alpha;
	float shininess;
	int tex_count;
	int alpha_count;
	int bump_count;
}

layout (location = 0) uniform sampler2D tex_unit;
layout (location = 1) uniform sampler2D alpha_unit;
layout (location = 2) uniform sampler2D bump_unit;

in vec3 normal;
in vec2 uv;
in vec3 light;

void main()
{
	
}