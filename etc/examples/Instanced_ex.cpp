

#include "turtle.h"

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



int main( int argc, char* args[] )
{
	
	// Create Window
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Instanced", 620,620 ); 
	MainEngine.HandleWindow(&window);
	
	// Shader
	GPUcodes gpucodes0=GPUcodes(&window,"./src/shaders_/instanced.shader");	
	

	gpucodes0.Load("instancedv","instancedf", "shader");
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	// A polygon will be made of triangles
	// As many as the sides
	int N = 50;
	InstancedObject Pentagon(2,5+1,5,2,GL_TRIANGLES,N,2);
	
	GenPolygon(&Pentagon,5,0.05);
	
	Pentagon.SpecifyBuffersAttributes("vposition", 2);
	Pentagon.SpecifyBuffersInstanceAttributes("voffset", 2,1);
    glCheckError();
    
    for (int i=0; i<N; i++)
	{	
		Pentagon.instance_buffer[i*2] = (rand()%100)/50.0-1.0; 
		Pentagon.instance_buffer[i*2+1] = (rand()%100)/50.0-1.0;
	}
    
	Pentagon.SetToOrigin(0);
	
	
	Scene test = Scene();
	test.LoadObject(&Pentagon, gpucodes0.glprograms[0]);
	
		
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	
	
	Pentagon.position[0] = 0.0;
	Pentagon.position[1] = 0.0;
	Pentagon.angle       = 0.0;
	
	
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes1=GPUcodes(&window,"./src/shaders_/font.shader");	
  gpucodes1.Load("fontV","fontF", "font");
  
  Texture fontTexture = Texture();
 
  fontTexture.LoadTexture(&window,"./etc/fonts/font.png",true,4, GL_RGBA);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  Textbox tbtext = Textbox("PRESS A", &pixelFont,1,7,0.1,0.1);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(-0.9,0.8,-0.0,0.0);
  test.LoadObject(&tbtext, gpucodes1.glprograms[0]);
	
	
	//window.CycleEnd();
	while( window.IsAlive() )
	{
		window.CycleStart();
	
		
	     if( kb[SDL_SCANCODE_A] == 1 )
	     {
	     for (int i=0; i<N; i++)
	     {	
		        Pentagon.instance_buffer[i*2] += ( (rand()%100)/50.0-1.0 ) *0.05   
		                - 2*float(Pentagon.instance_buffer[i*2]>1.0) + 2*float(Pentagon.instance_buffer[i*2]<-1.0);
		        Pentagon.instance_buffer[i*2+1] +=  ( (rand()%100)/50.0-1.0 ) *0.05
		                - 2*float(Pentagon.instance_buffer[i*2+1]>1.0) + 2*float(Pentagon.instance_buffer[i*2+1]<-1.0);
		        
		        
	     }
		 }
		
		test.Prepare();
		test.Update();
		window.CycleEnd();
		MainEngine.WindowsEvents();
	}
	

	return 0;
}
