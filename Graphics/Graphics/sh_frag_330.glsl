#version 330

layout(std140) uniform Material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emission;
	float shininess;
} mat;

varying vec3 gPosition; // before transforms
varying vec3 gNormal;	// before transforms
varying vec3 position;  // after transforms
varying vec3 normal;

uniform sampler2D grassTex;
uniform sampler2D dirtTex;
uniform sampler2D rockTex;
uniform sampler2D snowTex;

in vec3 lightPos;

const float PI = 3.1415926535897932384626433832795;
const float PI2 = PI/2.0f;


vec3 heightMapDiffuse(vec3 N, vec3 P)
{
	// float scale
	float S = 3;

	// scales the point
	vec3 TP = S * P;

	// planar uv
	vec2 uv = vec2(TP.x, TP.y);
	vec3 grass = texture(grassTex, uv).rgb;		//vec3(129.0/255.0, 178.0/255.0, 34.0/255.0);
	vec3 dirt = texture(dirtTex, uv).rgb;		//vec3(153.0/255.0, 155.0/255.0, 142.0/255.0);
	vec3 snow =  texture(snowTex, uv).rgb;		//vec3(220.0/255.0, 226.0/255.0, 229.0/255.0);

	// cylindrical uv
	float r = length(uv);
	float theta = S*(atan(TP.y/TP.x)/PI);
	uv = vec2(theta, TP.z);
	vec3 rock = texture(rockTex, uv).rgb;		//vec3(144.0/255.0, 99.0/255.0, 76.0/255.0);

	vec3 diffuse = vec3(0);

	// the vertical
	vec3 V = vec3(0, 0, 1);

	// calculates the angle between the vertical and the normal
	float angle = acos(dot(V, N));
	angle = angle > PI2 ? angle - PI2 : angle;

	// determine how close it is to PI/2
	float F = angle/PI2;



	// horizontal land type
	vec3 ground;
	float M;

	if (P.z < 0.15f)
	{
		ground = grass;
	}
	else if (P.z < .35f)
	{
		M = (.35f - P.z) / .2f;
		ground = (M * grass) + ((1.0-M) * dirt);
	}
	else if (P.z < .40f)
	{
		ground = dirt;
	}
	else if (P.z < .5f)
	{
		M = (.45f - P.z) / .05f;
		ground = (M * dirt) + ((1.0-M) * snow);
	}
	else
		ground = snow;

	// determines amounts
	diffuse += rock * F;
	diffuse += ground * (1.0 - F);

	return diffuse;
}

void main()
{
	// light info
	vec3 N = normalize(normal);
	vec3 L = normalize(lightPos - gPosition);
	float lambert = max(dot(L, N), 0.0);
	float spec = 0.0;
	
	// hard coded values due to broken material block
	vec3 diffuse = heightMapDiffuse(normalize(gNormal), gPosition);//vec3(.7, .7, .7);
	vec3 ambient = vec3(.05, .05, .05);
	vec3 specular = vec3(.1, .1, .1);
	float shininess = 0.05f;

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