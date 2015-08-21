#version 420

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

in vec4 Position;
in vec2 UV;

out vec4 vPosition;
out vec2 vUV;

uniform vec2 Test;

void main()
{
	vUV = UV;
	vPosition = Position;
	gl_Position = vec4(0.0f, 0.0f, 0.5f, 1.0f);
}
