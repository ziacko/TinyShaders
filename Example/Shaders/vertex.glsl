#version 420

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

layout (location = 0) in vec4 Position;
layout (location = 1) in vec2 UV;

void main()
{
	gl_Position = Position;
}
