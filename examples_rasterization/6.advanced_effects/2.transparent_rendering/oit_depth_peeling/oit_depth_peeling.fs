#version 330 core

uniform sampler2D depthTexture;

//current projected position, being z the depth. 
//Assuming x and y coordinates normalized, in [0..1] range. 
//To transform from standard [-1..1] coordinates to [0..1] 
//coordinates, you can do (pos.x+1)/2, for example.

in vec3 pos;

void main()
{
    if (pos.z <= texture(depthTexture, vec2(pos.x, pos.y))) 
        discard; //Manually performing the GL_GREATER depth test for each pixel

    //Rest of your shader code, if needed
}