#version 450

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

in vec4 Position;
out vec4 vPosition;

//uniform mat4 Projection;

void main()
{
	vPosition = vec4(1.0f, 1.0f, 0.1f, 1.0f);// * Projection;
	gl_Position = vPosition;
}
