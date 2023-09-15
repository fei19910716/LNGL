#version 330                                                                        
                                                                                    
layout (location = 0) in vec4   PV;
layout (location = 1) in vec4   Color;
layout (location = 2) in float  Life;
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = vec4(PV.xy, 0.0f, 1.0);
}