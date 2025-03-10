#version 430

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out float Alpha;

uniform mat4 model;
uniform mat4 projection;
uniform float alpha;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    Alpha=alpha;
}