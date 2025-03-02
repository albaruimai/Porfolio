#version 430
layout (location=0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 VPosition;

uniform mat4 model;
uniform mat4 view;


void main()
{ 
	VPosition = vec3(view *model* vec4(aPos, 1.0));
    
}