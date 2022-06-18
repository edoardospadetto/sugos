#include "window.h"

#include "../include/SDL&OpenGL.h"

#include "../modules_/debugmisc_module.h"




void Window_Class::SetMainWindow()
{
	lmainWindow = true;
}

void Window_Class::MakeCurrent(){ SDL_GL_MakeCurrent(this->gWindow, this->GLcontext);  }

Window_Class::Window_Class( Uint32 flags, std::string && name, int width_, int height_):
WIDTH(width_), HEIGHT(height_)
{

	
	//Create window
	gWindow = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags );
	IDWindow = SDL_GetWindowID( gWindow );
	if( gWindow == NULL )
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	
	}
		
	//Create context
	GLcontext = SDL_GL_CreateContext(this->gWindow );
	if( GLcontext == NULL )
	{
		printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
	
	}
	
#ifdef OPENGL_MACRO
	//Initialize GLEW
	glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
	}
#endif	

	//Use Vsync
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
	}
	
	
	glViewport(0, 0, WIDTH, HEIGHT);
	glDisable(GL_CULL_FACE); 
	
	if(lpixelart) //nopixealrt, I have no idea
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	

}



Window_Class::Window_Class( Uint32 flags, std::string && name): Window_Class(flags, std::move(name), 640,640) 
{
	

		
}



Window_Class::~Window_Class()
{

	//Destroy window
    	SDL_DestroyWindow( gWindow );
	//Quit SDL subsystems
    	SDL_Quit();
	gWindow = NULL;
	//screenSurface = NULL;

}



void Window_Class::CycleStart()
{	
	
	
	SDL_GL_MakeCurrent(this->gWindow, this->GLcontext);

	glClear ( GL_COLOR_BUFFER_BIT );
	
	glClear( GL_DEPTH_BUFFER_BIT );
	
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );
	

	
    //
	//EVENT THREAD
	
	//if(lmainWindow) userWatchdog = new std::thread(&Window_Class::, this);
	
}
int Window_Class::CycleEnd()
{

	//if (lmainWindow) userWatchdog->join();
	// What was not possible to execute in the thread;
	//if (lmainWindow) delete userWatchdog;
	
	SDL_GL_SwapWindow(this->gWindow);
	

	
	
	return 0; 
}

bool Window_Class::IsAlive()
{
	return(!exit);
}

Uint32  Window_Class::GetMousePosition(float &x, float&y)
{

	if(!this->mouseInside) return(-1);
	
	//Get Mouse Position
	int w,h;
	Uint32 button;
	
	button = SDL_GetMouseState(&w,&h);
	mouseX = 2*float(w)/this->WIDTH-1.0;
	mouseY = -2*float(h)/this->HEIGHT+1.0;
	x= mouseX;
	y= mouseY;
	
	return(button);
	
}

void Window_Class::Close()
{
	exit = true;
}

void Window_Class::Resize()
{
		
		SDL_GetWindowSize(gWindow, &WIDTH,&HEIGHT);
		dbglog("-- Resize Window", WIDTH,HEIGHT);
		
		//Fill the surface white
        //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );        
}
//Has to be executed by the main thread
void Window_Class::SDLQueue()
{
	if(lresize) SDL_GetWindowSize(gWindow, &WIDTH,&HEIGHT);
}

//OpenGl actions according to userWatchdog
void Window_Class::GLQueue()
{
	if(lresize) {glViewport(0, 0, WIDTH, HEIGHT); lresize=false;}
	
}

unsigned int Window_Class::GetTime()
{
	
	return SDL_GetTicks();
}


/*
void Window_Class::InitCPURender()
{
	 // We must call SDL_CreateRenderer in order for draw calls to affect this window.
        renderer = SDL_CreateRenderer(gWindow, -1, 0);

        // Select the color for drawing. It is set to red here.
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        // Up until now everything was drawn behind the scenes.
        // This will show the new, red contents of the window.
        SDL_RenderPresent(renderer);

}
*/

