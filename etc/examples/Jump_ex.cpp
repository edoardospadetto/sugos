#include <turtle.h>

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



VectorizedObject BuildPentagon()
{
	
	VectorizedObject Pentagon(6,5+1,5,2,GL_TRIANGLES);
	
	GenColoredPolygon(&Pentagon,5,0.3,0.5,1.0,1.0,1.0);
	
	Pentagon.SpecifyBuffersAttributes("r_", 2);
	Pentagon.SpecifyBuffersAttributes("c_", 4);
	
	
	Pentagon.SetToOrigin(0);
	
	
	Pentagon.LinkUniformToVariable("CM", 4, GL_FLOAT);
	
	return Pentagon;
}

float angle0 = 0;
float vii = 0.1;
float vinst = 0.0;
bool anim = false;
void MovePentagon(const Uint8* kb , VectorizedObject & Pentagon) 
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
	else
	{
		Pentagon.angle       = -M_PI*0.5;
	}
	
	
	vinst -= 0.0002;
	
	
	
		
	Pentagon.position[0] += 0.02*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(Pentagon.position[0]>1.0) + 												2*float(Pentagon.position[0]<-1.0);
	Pentagon.position[1] += vinst - 2*float(Pentagon.position[1]>1.0) + 										     2*float(Pentagon.position[1]<-1.0);;//0.02*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(Pentagon.position[1]>1.0) + 2*float(Pentagon.position[1]<-1.0);

	
	Pentagon.SetUniform("CM",0,Pentagon.position[0]);
	Pentagon.SetUniform("CM",1,Pentagon.position[1]);
	Pentagon.SetUniform("CM",2,Pentagon.angle);
	Pentagon.SetUniform("CM",3,0.0);
	
	
	
	
	

}


int main( int argc, char* args[] )
{
	
	// Create Window
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Jumping Shape", 640,640 ); 
	MainEngine.HandleWindow(&window);
	
	// Shader
	GPUcodes gpucodes0=GPUcodes(&window,"./src/shaders_/vectorizedobject.shader","#version 300 es");	
	gpucodes0.Load("vecv","vecf", "PositionRotationColor");
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	// A polygon will be made of triangles
	// As many as the sides
	
	Scene test = Scene();
	VectorizedObject Pentagon = BuildPentagon();
	test.LoadObject(&Pentagon, gpucodes0.glprograms[0]);
	
		
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes1=GPUcodes(&window,"./src/shaders_/font.shader");	
  gpucodes1.Load("fontV","fontF", "font");
  Texture fontTexture = Texture();
  fontTexture.LoadTexture(&window,"./etc/fonts/font.png",true,4, GL_RGBA);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  Textbox tbtext = Textbox("PRESS A P D", &pixelFont,1,11,0.1,0.1);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(-0.9,0.8,-0.0,0.0);
  test.LoadObject(&tbtext, gpucodes1.glprograms[0]);
		
		
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	
	
	Pentagon.position[0] = 0.0;
	Pentagon.position[1] = 0.0;
	Pentagon.angle       = -M_PI*0.5;
	
	
	
	

	

	while( window.IsAlive() )
	{
		 
		window.CycleStart();
	
		MovePentagon(kb, Pentagon);
	
		test.Prepare();

		test.Update();
		
	
		window.CycleEnd();


		MainEngine.WindowsEvents();
	
	}
	

	return 0;
}
