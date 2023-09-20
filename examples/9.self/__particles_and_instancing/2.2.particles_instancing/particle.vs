#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
layout (location = 2) in mat4 aInstanceMatrix;

out vec2 TexCoords;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = aInstanceMatrix * vec4(vertex.xy, 0.0f, 1.0f);
}