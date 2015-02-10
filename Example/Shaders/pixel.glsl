#version 420
in vec2 vUV;
in vec4 vPosition;

layout (location = 0) out vec4 outColour;

void main()
{
	outColour = vec4(1, 0.25f, 0.25f, 1.0f);
}