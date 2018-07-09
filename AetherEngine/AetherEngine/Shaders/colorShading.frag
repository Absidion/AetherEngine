#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor; //Using flat at the beginning of this ignores interpolation. Must be done in .vert as well.
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel
out vec4 color;

uniform sampler2D tex2D;

void main()
{

	vec4 textureColor = texture(tex2D, fragmentUV);

	color = textureColor * fragmentColor;
}