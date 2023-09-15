#version 330 core

layout (location = 0) in vec4   PV;
layout (location = 1) in vec4   Color;
layout (location = 2) in float  Life;

out VS_OUT {
    vec2   Position;
    vec2   Velocity;
    vec4   Color;
    float  Life;
} vs_out;

void main()
{
   vs_out.Position = PV.xy;
   vs_out.Velocity = PV.zw;
   vs_out.Color    = Color;
   vs_out.Life     = Life;
}