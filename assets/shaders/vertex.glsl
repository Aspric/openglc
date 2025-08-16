#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 color;

uniform float time;

void main()
{
	float a = 0.5 * (sin(time) + 1);
	float b = sin(time);
	gl_Position = vec4(aPos.x * b,aPos.y,aPos.z,1.0);
	color = aColor*a;
};