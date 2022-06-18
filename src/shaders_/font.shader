SHADER VERTEX fontV
#version 300 es
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec4 aColor;


out vec2 TexCoord;
out vec4 Color;


uniform vec4 CM;

void main()
{	

	float angle = CM[2];
	mat2 rotMat =  mat2(cos(angle),-sin(angle),
	     sin(angle),cos(angle));	


	vec2 tmp_pos =  rotMat* vec2(aPos.x,aPos.y) ;


	gl_Position = vec4(tmp_pos.x+CM[0], tmp_pos.y+CM[1] , CM[3] , 1.0);

	TexCoord = aTex;
	Color = aColor;
}

ENDSHADER

SHADER FRAGMENT fontF
#version 300 es
precision highp float;

out vec4 FragColor;
in vec2 TexCoord;
in vec4 Color;

uniform sampler2D uTexture;

void main()
{	
	vec4 txc = texture(uTexture, TexCoord);
	FragColor =  vec4( ( 1.0-txc.x ),1.0-txc.y,1.0-txc.z,txc.w)*Color;
	
} 

ENDSHADER
