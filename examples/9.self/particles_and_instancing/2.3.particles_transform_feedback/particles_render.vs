#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 4) in float fSize;

out float fSizePass;

void main()
{
   gl_Position = vec4(vPosition, 1.0);
   fSizePass   = fSize;
}