#version 330

varying vec2 uv;

varying vec4 vColor;

uniform sampler2D tex;

void main()
{
	// gets texture unit
	vec4 tex_unit = texture(tex, uv);

	// caculate final color
	gl_FragColor = tex_unit;
}