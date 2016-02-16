#version 420

/*
 *	very simple vertex shader that just transforms an object-space
 *	position into clip space and passes along a texture coordinate
 */

layout (location = 0) in vec4 Position;
layout (location = 1) in vec2 UV;

out defaultBlock
{
	vec4 position;
	vec2 UV;

} outBlock;


uniform vec2 Test;

void main()
{
	outBlock.UV = UV;
	outBlock.position = Position;
	gl_Position = vec4(0.0f, 0.0f, 0.5f, 1.0f);
}
