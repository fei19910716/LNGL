#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 3) in mat4 aInstanceMatrix;

out vec3 fColor;

void main()
{
    fColor = aColor;
    gl_Position = aInstanceMatrix * vec4(aPos, 1.0f); 
}