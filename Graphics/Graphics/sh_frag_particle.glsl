#version 330

varying vec2 uv;

varying vec4 vColor;

uniform sampler2D tex;

void main()
{
	// gets texture unit
	vec3 tex_unit = vec3(texture(tex, uv));

	float r = length(normalize(uv - vec2(.5,.5)));
	r = (r < 0) ? -r : r;


	// caculate final color
	gl_FragColor = vec4(tex_unit, r);
}