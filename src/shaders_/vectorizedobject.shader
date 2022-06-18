SHADER VERTEX vecv
#version 300 es

layout (location = 0) in vec2 r_;
layout (location = 1) in vec4 c_;

#define M_PI 3.1415926535897932384626433832795

uniform vec4 CM; 


out vec4 Color;



void main()
{	
    
      float angle = CM[2];
      mat2 rotMat =  mat2(cos(angle),-sin(angle),
                     sin(angle),cos(angle));	
                   
    vec2 tmp_pos =  rotMat* vec2(r_.x,r_.y) ;
 
    
    gl_Position = vec4(tmp_pos.x+CM[0], tmp_pos.y+CM[1] , CM[3] , 1.0);
       
     Color = c_;
}

ENDSHADER

SHADER FRAGMENT vecf
#version 300 es
precision highp float;

out vec4 FragColor;
in vec4 Color;

uniform sampler2D ourTexture;

void main()
{	
		
	
	
	FragColor = Color;
	
} 

ENDSHADER
