#include "./eventengine.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "./window.h"
#include "../modules_/debugmisc_module.h"


EventEngine::EventEngine(unsigned int fps_): fps(float(fps_))
{

	
}

void  EventEngine::HandleWindow(Window_Class* w)
{
	windows[w->IDWindow]= w;
}

void EventEngine::WindowsEvents()
{
	
	//Handle events on queue
	//Set Logicals for other functions
	SDL_Event event;
	
        while( SDL_PollEvent( &event ) != 0 )
        {
        	 
            //User requests quit
            switch( event.type)
			{
			
				case SDL_WINDOWEVENT :
#ifdef DEBUG
	
				SugosAssert(windows[event.window.windowID] != NULL,
				 	    "Error, window not under handle" );
#endif
					//-------------------------
					switch (event.window.event) 
					{
					
						 case SDL_WINDOWEVENT_RESIZED:				 	
						 case SDL_WINDOWEVENT_MAXIMIZED:
						
						        windows[event.window.windowID]->lresize = true;							
							//this->Resize();
							break;
						 case SDL_WINDOWEVENT_CLOSE:
						        windows[event.window.windowID]->exit = true;
						        break;
						 //Mouse enter
					        case SDL_WINDOWEVENT_ENTER:
						        windows[event.window.windowID]->mouseInside = true;
						        break;
					        //Mouse exit
					        case SDL_WINDOWEVENT_LEAVE:
						        windows[event.window.windowID]->mouseInside = false;
						        break;
						
						
						break;
						
					}
					break;
					
				case SDL_QUIT :
				
				 if( windows.size() > 1) 
				 {
				 	windows[event.window.windowID]->exit = true;
				 }
				
				break;
					//-------------------------
				
			}	
            
        }
	//Handle accordingly 
	for (auto w = windows.begin(); w != windows.end(); w++)
	{
		 w->second->SDLQueue();
		  w->second->GLQueue();
	}
	
	
	unsigned int now_frame = SDL_GetTicks() - frame_start;
#ifdef SHOWFPS
	std::cout <<  now_frame << "  " << 1000/fps << "  " << ( now_frame  < 1000/fps)  << "\n";
#endif
	if ( now_frame < 1000/fps ) SDL_Delay(1000/fps - now_frame);
	frame_start = SDL_GetTicks();
		
		
	

}
