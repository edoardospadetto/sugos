#include <turtle.h>
#include <random>

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );



void GenOffset(InstancedObject *obj, int instances, int size)
{


	for (int i=0; i<instances; i++)
	{	
		obj->instance_buffer[i*size] = (rand()%100)/200.0-0.25; 
		obj->instance_buffer[i*size+1] = -0.5;
	}
	 
	 //for (int i=0; i< 8 ; i++) std::cout << obj->instance_buffer[i] << " " ; 
}

void velset(float* vel)
{
	int N = 1000;
	for (int i=0; i<N; i++)
	{
		vel[i*2] = 0;
		vel[2*i+1] = abs(rand()%100)/10000.0+0.005;
	}

}

void UpdatePhys(float* pos, float* vel )
{
	int N = 1000;
	float a  = 0.0;
	for (int i=0; i<N; i++)
	{
		
		vel[2*i+1] += (rand()%100 - 50 )/100000;
		vel[2*i] += 0 ;
		pos[2*i]    += vel[2*i];
		pos[2*i+1]  += vel[2*i+1];
		
		if(  abs(pos[2*i]*pos[2*i]+ (pos[2*i+1]+0.5)*(pos[2*i+1]+0.5) ) > (rand()%100) / 100.0 )
		{
			pos[i*2] = (rand()%100)/200.0-0.25;
			pos[i*2+1] =-0.5;
			//vel[i*2] = (rand()%100 - 50 )/10000.0;
			vel[2*i+1] = abs(rand()%100)/1000.0+0.005;
			
		}
	}

}


int main( int argc, char* args[] )
{
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Instanced Rendering", 620,620 ); 
	MainEngine.HandleWindow(&window);
	
	GPUcodes gpumodule=GPUcodes(&window,"./src/shaders_/instanced.shader","#version 300 es");	

	gpumodule.Load("instancedv","instancedf", "shader");
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	int N = 1000;
	
  	
	InstancedObject Triangle(2,4,3,2,GL_TRIANGLES, N,2);
	
	float* velocities=new float[2*N];
	memset(velocities,0.0,2*N);
	velset(velocities);
	
	Triangle.SpecifyBuffersAttributes("vposition", 2) ;
	Triangle.SpecifyBuffersInstanceAttributes("voffset", 2,1) ;
  	
	GenPolygon(&Triangle,3,0.02);
	Triangle.SetToOrigin(0);
	GenOffset(&Triangle, N, 2);	
	
	Scene test = Scene();
	
	test.LoadObject(&Triangle, gpumodule.glprograms[0]);
		
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	
	
	while( window.IsAlive() )
	{
		window.CycleStart();

		Triangle.lmodtb=true;
		UpdatePhys(Triangle.instance_buffer, velocities);
		test.Update();
		test.Prepare();
		//test.ReBuffer();
		//GenOffset(&Triangle, 20, 2);
		
		window.CycleEnd();
		MainEngine.WindowsEvents();
	}
	

	return 0;
}
