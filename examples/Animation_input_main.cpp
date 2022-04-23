

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
	
	Texture monkSpriteSheet;
	monkSpriteSheet.LoadTexture("./assets/monkspritesheey.png", true, 4, GL_RGBA);
	
	State run("./conf/monkrun.anim", &monkSpriteSheet), attack("./conf/monkattack.anim", &monkSpriteSheet);
	run.ConnectTo(&attack, SDL_SCANCODE_UP , ON_PRESS);
	attack.ConnectTo(&run, SDL_SCANCODE_UP , ON_RELEASE );
	
	StateEngine monkanim(&window); 
	monkanim.AddState(&run);
	monkanim.AddState(&attack);
	// Shader
	GPUcodes gpucodes0=GPUcodes("./shaders/shader_anim");	

	gpucodes0.Load("simpletexture0","simpletexture1", "simplea");
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
		
	AnimatedObject2D MonkChar(4,4,1,2,4,&monkanim);
	
	GenQuadText(MonkChar);	
	MonkChar.SetToOrigin(0);
	MonkChar.Rescale(0,0.7);
	//MonkChar.SetSnapshot(0, 0);

	MonkChar.LinkUniformToVariable("status", 2);

	MonkChar.SpecifyBuffersAttributes("aPos", 2, GL_QUADS);	
	MonkChar.SpecifyBuffersAttributes("aTex", 2, GL_QUADS);

	Scene test = Scene();
	test.LoadObj(MonkChar, gpucodes0.glprograms[0]);	
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	int counter = 0;
	//While application is running
	
	while( window.IsAlive() )
	{
		window.CycleStart();
		/*if(counter == 20) 
		{
			
			MonkChar.RightSnapshot();	
			test.Prepare();
			counter = 0;
		}
		else 
		{
			counter+=1;
		}
*/	
		
		
		//shootDirectionY = -kb[SDL_SCANCODE_UP] + kb[SDL_SCANCODE_DOWN];
	    	
		MonkChar.position[0]+= 0.02*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(MonkChar.position[0]>1.0) + 2*float(MonkChar.position[0]<-1.0);
		MonkChar.position[1] += 0.02*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(MonkChar.position[1]>1.0) + 2*float(MonkChar.position[1]<-1.0);

	

		MonkChar.SetUniform("status",0,MonkChar.position[0]);
		MonkChar.SetUniform("status",1,MonkChar.position[1]);
	
		//glProgramUniform3f(gpucodes0.glprograms[0],status,angle,Spaceship.position[0],Spaceship.position[1]);
		
		test.Update();
		test.Prepare();
		//render(gVBO,gIBO,gpucodes0.glprograms[0]);

		//Update screen
		window.CycleEnd();
	}
	

	return 0;
}
