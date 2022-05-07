

SHADER VERTEX debug_colliders_vertex

#version 330 core
layout (location = 0) in vec2 aPos;
uniform vec3 c;
void main()
{	

    mat2 rotMat =  mat2(cos(c.z),-sin(c.z),
                        sin(c.z),cos(c.z));	
                   
    vec2 tPos =  rotMat* vec2(aPos.x,aPos.y) ;
    gl_Position = vec4(tPos.x+c.x, tPos.y+c.y, 0.0, 1.0);
}

ENDSHADER

SHADER FRAGMENT debug_colliders_fragment

#version 330 core

out vec4 FragColor;


void main()
{			
	FragColor =  vec4(1.0, 0.0, 0.0, 1.0);
} 

ENDSHADER



