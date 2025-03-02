#version 430
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec4 LightPosition;
uniform float LightIntensity;
uniform sampler2D texture_diffuse1;

layout( location = 0 ) out vec4 Ambient;
layout( location = 1 ) out vec4 DiffSpec;

void main() {
    vec3 toLight = normalize(vec3(LightPosition) - FragPos);
	vec3 toV = normalize(vec3(-FragPos));
	vec3 r = reflect( -toLight, Normal );

	float diffuse = max(0.5f, dot(Normal, toLight));
	float specular = pow(max(0.0, dot(r, Normal)), 640.0);

	Ambient = vec4(texture(texture_diffuse1, TexCoord)) * 0.2f *LightIntensity;
    DiffSpec =vec4(texture(texture_diffuse1, TexCoord))*(diffuse+specular)*LightIntensity+Ambient;
}