SHADER VERTEX texturev

#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;


out vec2 TexCoord;

uniform vec3 status;

void main()
{	
    gl_Position = vec4(aPos.x+status[0], aPos.y+status[1], status[2], 1.0);
    TexCoord = aTex;
}

ENDSHADER

SHADER FRAGMENT texturef

#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{	
		
	FragColor = texture(ourTexture, TexCoord);
	
} 

ENDSHADER
