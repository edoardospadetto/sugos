

#include "turtle.h"

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



int main( int argc, char* args[] )
{
	
	// Create Window
	Window_Class window = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN ); 
	
	
	// Shader
	GPUcodes gpucodes0=GPUcodes("./shaders/vectorizedobjectnc.shader");	

	gpucodes0.Load("vecv","vecf", "vv");
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	PhysicsObject2D Square(2,4,1,2,GL_QUADS), Triangle(2,3,1,2,GL_TRIANGLES);
	
	
	
	
	Triangle.SpecifyBuffersAttributes("r_", 2) ;
	Square.SpecifyBuffersAttributes("r_", 2) ;
	
	Square.LinkUniformToVariable("CM", 4);
	Triangle.LinkUniformToVariable("CM", 4);

	
	
	GenQuad(Square);
	GenTriangle(Triangle);	
	Square.SetToOrigin(0);
	Triangle.SetToOrigin(0);
	
	Triangle.Rescale(0, 5.0);
	Triangle.SetToOrigin(0);
	Square.Rescale(0, 2.0);
	
	Triangle.SameShapeCollider(0, GENERIC);
	Square.SameShapeCollider(0, GENERIC);

	
	
	Scene test = Scene();
	test.LoadObj(Square, gpucodes0.glprograms[0]);
	test.LoadObj(Triangle, gpucodes0.glprograms[0]);
	

	Square.collider->xc = &(Square.position[0]);
	Square.collider->yc = &(Square.position[1]);
	Square.collider->angle = &(Square.angle);
	Triangle.collider->xc = &(Triangle.position[0]);
	Triangle.collider->yc = &(Triangle.position[1]);
	Triangle.collider->angle = &(Triangle.angle);
	
	test.DebugColliders();
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	int counter = 0;
	
	
	while( window.IsAlive() )
	{
		window.CycleStart();
	
		Triangle.position[0]+= 0.005*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(Triangle.position[0]>1.0) + 2*float(Triangle.position[0]<-1.0);
		Triangle.position[1] += 0.005*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(Triangle.position[1]>1.0) + 2*float(Triangle.position[1]<-1.0);
		Triangle.angle +=  0.005*(-kb[SDL_SCANCODE_Z] + kb[SDL_SCANCODE_X])  ;
		
		Triangle.SetUniform("CM",0,Triangle.position[0]);
		Triangle.SetUniform("CM",1,Triangle.position[1]);
		Triangle.SetUniform("CM",2,Triangle.angle);
		Square.SetUniform("CM",0,Square.position[0]);
		Square.SetUniform("CM",1,Square.position[1]);
		Square.SetUniform("CM",2,Square.angle);
		
		
	
		test.Update();
		test.Prepare();
	
		window.CycleEnd();
	}
	

	return 0;
}
