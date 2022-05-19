

#include "turtle.h"

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



PhysicsObject2D BuildPentagon()
{

	PhysicsObject2D Pentagon(6,5+1,5,2,GL_TRIANGLES);
	
	GenColoredPolygon(&Pentagon,5,0.3,0.5,1.0,1.0,1.0);
	
	Pentagon.SpecifyBuffersAttributes("r_", 2);
	Pentagon.SpecifyBuffersAttributes("c_", 4);
	
	
	Pentagon.SetToOrigin(0);
	
	Collider2D GenPolygonCollider(VectorizedObject &Pentagon, bool colored=true);
	
	Pentagon.LinkUniformToVariable("CM", 4);
	
	return Pentagon;
}

float angle0 = 0;
float vii = 0.1;
float vinst = 0.0;
bool anim = false;
void MovePentagon(const Uint8* kb , PhysicsObject2D & Pentagon) 
{

	
	if (anim && Pentagon.angle-angle0 <  2*M_PI*0.2 )
	{
		
		Pentagon.angle+= 2*M_PI*0.2*vii;
	}
	else if(anim)
	{
		anim=false;
		SetColor(&Pentagon, 5 ,0.5,1.0,1.0,1.0);
		
	}
	else if ( kb[SDL_SCANCODE_P]) 
	{
		SetColor(&Pentagon, 5 ,1.0,0.5,1.0,1.0);
		anim= true;
		angle0 = Pentagon.angle;
		Pentagon.angle+= 2*M_PI*0.2* kb[SDL_SCANCODE_P]*vii;
		vinst=0.01;
	}
	
	
	vinst -= 0.0002;
	
	
	
		
	Pentagon.position[0] += 0.02*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(Pentagon.position[0]>1.0) + 2*float(Pentagon.position[0]<-1.0);
	Pentagon.position[1] += vinst;//0.02*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(Pentagon.position[1]>1.0) + 2*float(Pentagon.position[1]<-1.0);


	Pentagon.SetUniform("CM",0,Pentagon.position[0]);
	Pentagon.SetUniform("CM",1,Pentagon.position[1]);
	Pentagon.SetUniform("CM",2,Pentagon.angle);
	Pentagon.SetUniform("CM",3,0.0);
	
	
	
	
	

}


int main( int argc, char* args[] )
{
	
	// Create Window
	Window_Class window = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN ); 
	window.OpenGLInit();
	
	// Shader
	GPUcodes gpucodes0=GPUcodes("./shaders/light0attempt.shader");	

	gpucodes0.Load("vecv","vecf", "PositionRotationColor");
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	// A polygon will be made of triangles
	// As many as the sides
	
	Scene test = Scene();
	PhysicsObject2D Pentagon = BuildPentagon();
	test.LoadObj(Pentagon, gpucodes0.glprograms[0]);
	
		
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	
	
	Pentagon.position[0] = 0.0;
	Pentagon.position[1] = 0.0;
	Pentagon.angle       = -M_PI*0.5;
	
	
	
	//window.CycleEnd();
	while( window.IsAlive() )
	{
		window.CycleStart();
	
		
		
		MovePentagon(kb, Pentagon);
		
		//dbglog(Pentagon.angle);
		
		
		test.Prepare();
		test.Update();
		window.CycleEnd();
	}
	

	return 0;
}
