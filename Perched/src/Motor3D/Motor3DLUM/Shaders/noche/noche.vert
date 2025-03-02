#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
 
out vec2 TexCoords;
out vec3 FragPos;  
out vec3 Normal;
out float alpha;
out float gl_ClipDistance[6];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 projViewModel;
uniform float scale;
uniform float alpha_v;
uniform mat3 NormalMatrix;


void main()
{
    TexCoords = aTexCoords; 
   // Normal = normalize( NormalMatrix * aNormal);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
  
    FragPos = vec3(model * vec4(aPos, 1.0));
    alpha = alpha_v;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}