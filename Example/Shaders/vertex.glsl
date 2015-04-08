#version 450

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

in vec4 Position;
out vec4 vPosition;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
	vPosition = Projection * View * Model * Position;
	gl_Position = vPosition;
}
