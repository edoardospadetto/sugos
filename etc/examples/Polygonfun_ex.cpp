#include "turtle.h"


//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



int main( int argc, char* args[] )
{
	
	Window_Class window = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN ); 
	
	
	GPUcodes gpucodes0=GPUcodes("./shaders/shader0");	

	gpucodes0.Load("simple0","simple1", "simple");
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	VectorizedObject Triangle(2,4,3,2,GL_TRIANGLES);
	
	
	Triangle.SpecifyBuffersAttributes("aPos", 2) ;
	Triangle.LinkUniformToVariable("status", 2);

	
	GenPolygon(&Triangle,3,1);

	Triangle.SetToOrigin(0);

	Scene test = Scene();
	
	test.LoadObject(&Triangle, gpucodes0.glprograms[0]);
		
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	
	
	while( window.IsAlive() )
	{
		window.CycleStart();

		Triangle.position[0]+= 0.005*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(Triangle.position[0]>1.0) + 2*float(Triangle.position[0]<-1.0);
		Triangle.position[1] += 0.005*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(Triangle.position[1]>1.0) + 2*float(Triangle.position[1]<-1.0);
		Triangle.SetUniform("status",0,Triangle.position[0]);
		Triangle.SetUniform("status",1,Triangle.position[1]);
		
	
		test.Update();
		test.Prepare();
		
		window.CycleEnd();
	}
	

	return 0;
}
