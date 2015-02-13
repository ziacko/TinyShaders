#version 420
in vec2 vUV;
in vec4 vPosition;

out vec4 outColour;

uniform vec4 TestColor;

void main()
{
	outColour = vec4(255, 0, 255, 1);
}