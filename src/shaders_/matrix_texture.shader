SHADER VERTEX texturev

#version 330 core
layout (location = 0) in vec2 aPos;


void main()
{	
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);    
}


ENDSHADER

SHADER FRAGMENT texturef

#version 330 core


uniform vec2 m_sizes;
uniform vec2 w_sizes;
uniform sampler2D ourTexture;
out vec4 FragColor;

layout( origin_upper_left) in vec4 gl_FragCoord;

void main()
{	
	//vec4 Tfilter = vec4(1.0, 1.0, 1.0, 0.5);
	vec2 pos = vec2(gl_FragCoord.x/w_sizes.x,gl_FragCoord.y/w_sizes.y) ;	

	ivec2 iPos = ivec2( int(pos.x*m_sizes.x), int(pos.y*m_sizes.y));
	

	
    //if( length( pos-0.05 - cell) >0.01) coloro = vec4( 0.0, 0.0,1.0,1.0);
    //else coloro  = vec4( 0.0, 1.0,1.0,1.0);
	   
    float value =  texelFetch(ourTexture, iPos,0).x;
    float value2 = 1.0;
    if(value > 0.45) value2 = 0.5;
    if(value > 0.5) value2 = 0.0;
    gl_FragColor = vec4(1.0,1.0,1.0,value*value*value*value*value*value*20);
            
}


ENDSHADER
