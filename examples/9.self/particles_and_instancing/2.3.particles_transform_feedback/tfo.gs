#version 330 core

layout(points) in;
layout(points, max_vertices = 30) out;

in VS_OUT {
    vec2   Position;
    vec2   Velocity;
    vec4   Color;
    float  Life;
} gs_in[];

out vec2   outPosition;
out vec2   outVelocity;
out vec4   outColor;
out float  outLife;

#define TOTAL_PARTICLE 1000
#define NEW_PARTICLE   5

void main()
{
    outPosition = gs_in[0].Position;
    outVelocity = gs_in[0].Velocity;
    outColor = gs_in[0].Color;
    outLife = gs_in[0].Life;

    if(outLife > 0.0f){
        // update particle
        outLife -= 0.001f;
        outPosition += outVelocity * 0.001f;

        EmitVertex();
        EndPrimitive();
    }else{
        for(int i = 0; i < NEW_PARTICLE; i++)
        {
            if( i % 2 == 0){
                outVelocity = vec2(1.0f,1.0f);
            }else{
                outVelocity = vec2(-1.0f,1.0f);
            }
            outPosition = vec2(0.0f,-0.9f);
            
            outColor = vec4(1.0f);
            outLife = 1.0f;
            EmitVertex();
            EndPrimitive();
        }
    }
}