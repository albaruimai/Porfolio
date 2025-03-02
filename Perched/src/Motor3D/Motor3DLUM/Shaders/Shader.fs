#version 330 core
in vec2 TexCoords;
in float Alpha;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    color = vec4(spriteColor, Alpha) * texture(image, TexCoords);
} 