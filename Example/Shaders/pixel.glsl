#version 420

in defaultBlock
{
	vec4 position;
	vec2 UV;

} inBlock;

out vec4 outColour;

uniform vec4 TestColor;

void main()
{
	outColour = vec4(255, 0, 255, 1);
}