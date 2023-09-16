#version 330                                                                        
                                                                                    
uniform sampler2D gColorMap;                                                        
                                                                                    
in vec2 TexCoord; 
// flat in vec4 vColorPart;


out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(gColorMap, TexCoord);  
    // FragColor = vec4(vTexColor.xyz, 1.0)*vColorPart;                                   

    if (FragColor.r >= 0.9 && FragColor.g >= 0.9 && FragColor.b >= 0.9) {           
        discard;                                                                    
    }                                                                               
}