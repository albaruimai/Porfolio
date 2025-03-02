#version 430

layout (location = 0) in vec3 aPos;

in vec3 VPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 projViewModel;
void main()
{
  
    gl_Position = vec4(aPos, 1.0);
}
