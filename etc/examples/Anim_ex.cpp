

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
	GPUcodes gpucodes0=GPUcodes("./shaders/shader0");	
	
	gpucodes0.Load("simple0","simple2", "simpleb");
	
	gpucodes0.Load("simpletexture0","simpletexture1", "simplea");
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	AnimatedObject2D Spaceship{AnimatedObject2D(2,3,1,2,GL_TRIANGLES)};
	AnimatedObject2D Spaceship2{AnimatedObject2D(4,4,1,2,GL_QUADS)};
	AnimatedObject2D Spaceship3{AnimatedObject2D(4,3,1,2,GL_TRIANGLES)};
	
	std::vector<AnimatedObject2D*> projectiles;
	
	GenTriangle(Spaceship);
	GenTriText(Spaceship3);
	GenQuadText(Spaceship2);
		

	Spaceship.SetToOrigin(0);
	Spaceship2.SetToOrigin(0);
	Spaceship3.SetToOrigin(0);
	
	float vec1[2]={0.8,0.4},vec2[2]={-0.4,-0.4}, vec3[2]={0.0,-0.4};

	
	Spaceship2.LoadTexture("./assets/pngegg.png", true,4, GL_RGBA);


		
	//Enable text input
	float color=1, angle=0; 
	//Enable text input
	
	Spaceship.LinkUniformToVariable("status", 2);
	Spaceship2.LinkUniformToVariable("status", 2);
	Spaceship3.LinkUniformToVariable("status", 2);
	

	Spaceship.SpecifyBuffersAttributes("aPos", 2);
	Spaceship2.SpecifyBuffersAttributes("aPos", 2);
	Spaceship2.SpecifyBuffersAttributes("aTex", 2);
	Spaceship3.SpecifyBuffersAttributes("aPos", 2);
	Spaceship3.SpecifyBuffersAttributes("aTex", 2);


	Scene test = Scene();
	test.LoadObj(Spaceship2, gpucodes0.glprograms[1]);
	
	test.LoadObj(Spaceship, gpucodes0.glprograms[0]);
	test.LoadObj(Spaceship3, gpucodes0.glprograms[1]);		
	
			
	
		
		
	
	test.Prepare();

	const Uint8* kb = SDL_GetKeyboardState(NULL);


	//While application is running
	while( window.IsAlive() )
	{
		window.CycleStart();
		
		//shootDirectionY = -kb[SDL_SCANCODE_UP] + kb[SDL_SCANCODE_DOWN];
	    	Spaceship.position[0]+= 0.02*(-kb[SDL_SCANCODE_LEFT] + kb[SDL_SCANCODE_RIGHT]) - 2*float(Spaceship.position[0]>1.0) + 2*float(Spaceship.position[0]<-1.0);
		Spaceship.position[1] += 0.02*(-kb[SDL_SCANCODE_DOWN] + kb[SDL_SCANCODE_UP]) - 2*float(Spaceship.position[1]>1.0) + 2*float(Spaceship.position[1]<-1.0);
		Spaceship2.position[0]+= 0.02*(-kb[SDL_SCANCODE_A] + kb[SDL_SCANCODE_D]) - 2*float(Spaceship2.position[0]>1.0) + 2*float(Spaceship2.position[0]<-1.0);
		Spaceship2.position[1] += 0.02*(-kb[SDL_SCANCODE_S] + kb[SDL_SCANCODE_W]) - 2*float(Spaceship2.position[1]>1.0) + 2*float(Spaceship2.position[1]<-1.0);
		Spaceship3.position[0]=Spaceship2.position[1]+0.1;
		Spaceship3.position[1]=Spaceship2.position[1]+0.1;
		
		if(kb[SDL_SCANCODE_H])
		{
			AnimatedObject2D *tmp = new AnimatedObject2D(2,4,1,2,4);
			GenProj(*tmp);
			//
			//
			tmp->SpecifyBuffersAttributes("aPos", 2, GL_QUADS);
			tmp->LinkUniformToVariable("status", 2);
			test.LoadObj(*tmp, gpucodes0.glprograms[0]);
			projectiles.push_back(tmp);
			tmp->position[0]=Spaceship.position[0];
			tmp->position[1]=Spaceship.position[1];
			tmp->SetUniform("status",0,tmp->position[0]);
			tmp->SetUniform("status",1,tmp->position[1]);
			test.Prepare();
		}
		int deleted =0;
		for(auto p = projectiles.end()-1;p!=projectiles.begin()-1;--p )
		{
			(*p)->position[0]+=0.05;
			(*p)->SetUniform("status",0,(*p)->position[0]);
			(*p)->SetUniform("status",1,(*p)->position[1]);
			if ((*p)->position[0] > 1)	
			{
				test.UnloadObject(**p);
				delete (*p);
				p = projectiles.erase(p);
				dbglog("test A");
				deleted+=1;
			}
	
			
			
		}

		Spaceship.SetUniform("status",0,Spaceship.position[0]);
		Spaceship.SetUniform("status",1,Spaceship.position[1]);
		Spaceship2.SetUniform("status",0,Spaceship2.position[0]);
		Spaceship2.SetUniform("status",1,Spaceship2.position[1]);
		Spaceship3.SetUniform("status",0,Spaceship3.position[0]);
		Spaceship3.SetUniform("status",1,Spaceship3.position[1]);
	
		//glProgramUniform3f(gpucodes0.glprograms[0],status,angle,Spaceship.position[0],Spaceship.position[1]);
		test.Render();
		
		//render(gVBO,gIBO,gpucodes0.glprograms[0]);

		//Update screen
		window.CycleEnd();
	}

	return 0;
}
