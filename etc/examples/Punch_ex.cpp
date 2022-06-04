

#include <turtle.h>

void render();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


GLint gVertexPos2DLocation = -1;



int main( int argc, char* args[] )
{
	
	// Create Window
	EventEngine MainEngine=EventEngine(60);
	Window_Class window = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN,"Punch_ex", 640,320 ); 
	MainEngine.HandleWindow(&window);
	 
	window.SetMainWindow();
	Texture monkSpriteSheet;
	monkSpriteSheet.LoadTexture(&window,"./etc/spritesheets/monkspritesheey.png", true, 4, GL_RGBA);
	
	State run("./etc/animconffiles/monkrun.anim", &monkSpriteSheet), attack("./etc/animconffiles/monkattack.anim", &monkSpriteSheet);
	run.ConnectTo(&attack, SDL_SCANCODE_UP , ON_PRESS);
	attack.ConnectTo(&run, TIME_OUT , UNDEFINED );
	
	StateEngine monkanim(&window); 
	monkanim.AddState(&run);
	monkanim.AddState(&attack);
	// Shader
	GPUcodes gpucodes0=GPUcodes(&window, "./src/shaders_/anim.shader");	

	gpucodes0.Load("texturev","texturef", "simplea");
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
		
	AnimatedObject2D MonkChar(4,4,1,2,GL_QUADS,&monkanim);
	
	GenQuadText(MonkChar);	
	MonkChar.SetToOrigin(0);
	MonkChar.Rescale(0,0.7);
	//MonkChar.SetSnapshot(0, 0);

	MonkChar.LinkUniformToVariable("status", 2);

	MonkChar.SpecifyBuffersAttributes("aPos", 2);	
	MonkChar.SpecifyBuffersAttributes("aTex", 2);

	Scene test = Scene();
	test.LoadObj(MonkChar, gpucodes0.glprograms[0]);	
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	int counter = 0;
	//While application is running
	
	while( window.IsAlive() )
	{
		window.CycleStart();

	    	
		MonkChar.position[0]+= 0.02*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(MonkChar.position[0]>1.0) + 2*float(MonkChar.position[0]<-1.0);
		MonkChar.position[1] += 0.02*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(MonkChar.position[1]>1.0) + 2*float(MonkChar.position[1]<-1.0);

	

		MonkChar.SetUniform("status",0,MonkChar.position[0]);
		MonkChar.SetUniform("status",1,MonkChar.position[1]);
	
		test.Prepare();
		test.Update();

		window.CycleEnd();
		MainEngine.WindowsEvents();
	}
	

	return 0;
}
