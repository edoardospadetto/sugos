
class Window_Class

{


	
		  SDL_Window* gWindow = NULL;
		  SDL_Surface* screenSurface = NULL;
		  SDL_DisplayMode DM;
		  SDL_GLContext  GLcontext;
			
		  //Screen dimension constants
		  int WIDTH = 640;
		  int HEIGHT = 640;
		  
		  float fps = 60 ;
		  std::thread *userWatchdog =NULL;
		  
		  bool lpixelart   = true;
		  bool lmainWindow = false; 

		  // state vars 
		   
     private:  
		bool exit = false; 
		void WindowEvents();
		void SDLQueue();
		void GLQueue();
		
		bool lresize=false;
		void Resize();
		
		unsigned int frame_start = 0; 
		 

         public :	
	
		 const Uint8* kb;
		  Window_Class(unsigned int fps_, Uint32 flags,  std::string && name);
		  Window_Class(unsigned int fps_, Uint32 flags, std::string && name, int width_, int height_);
		  ~Window_Class();
		  unsigned int GetTime();
		  bool IsAlive();
		  void CycleStart();
		  void MakeCurrent();
		 

		  void Close();
		  int CycleEnd();
		  void SetMainWindow();
		  




};


void Window_Class::SetMainWindow()
{
	lmainWindow = true;
	
	
	

	
	
}

void Window_Class::MakeCurrent(){ SDL_GL_MakeCurrent(this->gWindow, this->GLcontext);  }

Window_Class::Window_Class(unsigned int fps_, Uint32 flags, std::string && name, int width_, int height_):
WIDTH(width_), HEIGHT(height_), fps(float(fps_))
{

	if (SDL_WasInit(SDL_INIT_VIDEO) == 0) 
	{
	//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			
		}
	}
	
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	kb = SDL_GetKeyboardState(NULL);
	
	
	//Create window
	gWindow = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags );
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
	
	//Initialize GLEW
	glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
	}
	

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



Window_Class::Window_Class(unsigned int fps_, Uint32 flags, std::string && name): Window_Class(fps_, flags, std::move(name), 640,640) 
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
	frame_start = SDL_GetTicks();
	SDL_GL_MakeCurrent(this->gWindow, this->GLcontext);
	glClear ( GL_COLOR_BUFFER_BIT );
	glClear( GL_DEPTH_BUFFER_BIT );
	glClearColor ( 0.0, 0.0, 0.0, 1.0 );

	
    //
	//EVENT THREAD
	
	if(lmainWindow) userWatchdog = new std::thread(&Window_Class::WindowEvents, this);
	
}
int Window_Class::CycleEnd()
{

	if (lmainWindow) userWatchdog->join();
	GLQueue(); // What was not possible to execute in the thread;
	if (lmainWindow) delete userWatchdog;
	
	
	SDL_GL_SwapWindow(this->gWindow);

	unsigned int now_frame = SDL_GetTicks() - frame_start;
	
	if(lmainWindow)
	{
		if ( now_frame < 1000/fps ) SDL_Delay(1000/fps - now_frame);
	}	
		
	//printf("%d \n", now_frame);
	//printf("\n");
	return 0; 
}

bool Window_Class::IsAlive()
{
	return(!exit);
}

void Window_Class::WindowEvents()
{
	//Handle events on queue
	//Set Logicals for other functions
	SDL_Event event;
	
        while( SDL_PollEvent( &event ) != 0 )
        {
        	 
            //User requests quit
            switch( event.type)
			{
			
				case SDL_QUIT :
					exit = true;
					break;
					
				
				case SDL_WINDOWEVENT :
					
					//-------------------------
					switch (event.window.event) 
					{
						 case SDL_WINDOWEVENT_RESIZED:				 	
						 case SDL_WINDOWEVENT_MAXIMIZED:
						
							lresize = true;							
							//this->Resize();
							break;
						case SDL_WINDOWEVENT_CLOSE:
						exit = true;
						
						break;
						
					}
					break;
					//-------------------------
				
			}	
            
        }
	//Handle accordingly 
	SDLQueue();
	
	
	

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
	if(lresize) glViewport(0, 0, WIDTH, HEIGHT); lresize=false;
	
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

