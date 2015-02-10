#version 330

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

in vec4 Position;
in vec2 UV;

out vec4 vPosition;
out vec2 vUV;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float Time;
uniform float Interpolation;

uniform mat4 Bones[128];

void main()
{
	vUV = UV;
	vPosition = Position;
	gl_Position = vec4(0.95f, 0.65f, 0.5f, 1.0f);
}
