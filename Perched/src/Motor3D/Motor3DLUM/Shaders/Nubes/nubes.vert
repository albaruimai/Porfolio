#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
out float LightIntensity;


out vec3 Position;  
out vec3 Normal;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform mat3 NormalMatrix;
uniform vec3 LightPos;

void main()
{
  
    TexCoord = aTexCoords; 
	Normal = normalize( NormalMatrix * aNormal);
    gl_Position = projection * view *model* vec4(aPos, 1.0);
    Position = vec3(view * vec4(aPos, 1.0));
    LightIntensity	= dot(normalize(LightPos - aPos),Normal);
    LightIntensity*=1.5;


}
 

