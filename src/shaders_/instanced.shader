SHADER VERTEX instancedv
#version 300 es 

layout(location = 0) in vec2 vposition;     
layout(location = 2) in vec2 voffset;     // the per instance offset
out vec4 fcolor;    

void main() {    
	fcolor = vec4(abs(voffset.y+1.0),0,abs(voffset.y-1.0)*abs(voffset.y-1.0),1.0);
	gl_Position =  vec4(voffset.x+vposition.x,voffset.y+vposition.y, 0.0, 1.0);
}

ENDSHADER

SHADER FRAGMENT instancedf
#version 300 es
precision highp float;

in vec4 fcolor;    
layout(location = 0) out vec4 FragColor;    

void main() {    
	FragColor = fcolor;    
}

ENDSHADER
