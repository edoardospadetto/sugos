SHADER VERTEX 3Dsimplev
#version 330 core

in vec3 p3d_Vertex;
in vec2  vTexCoord;
in vec3  vnormals;
out vec2 fTexCoord;
in vec3 b;

void main()
{
  gl_Position =  vec4( p3d_Vertex.x,p3d_Vertex.y,-1*p3d_Vertex.z,1.0);
  fTexCoord=vTexCoord;
}

ENDSHADER

SHADER FRAGMENT 3Dsimplef
#version 330 core
out vec4 fragColor;
in vec2 fTexCoord;
uniform sampler2D uTexture;

void main() {
  fragColor = texture(uTexture, fTexCoord);
  //fragColor = vec4(0.5,1.0,1.0,1.0);
}
ENDSHADER
