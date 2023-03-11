#include "./eventengine.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "./window.h"
#include "../modules_/debugmisc_module.h"
#ifdef EMSCRIPTEN_MACRO
#include <emscripten.h>
#endif
/*
int main() {
    // Initialize the joystick subsystem
    SDL_Init(SDL_INIT_JOYSTICK);

    // If there are no joysticks connected, quit the program
    if (SDL_NumJoysticks() <= 0) {
        printf("There are no joysticks connected. Quitting now...\n");
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK)
        return -1;
    }

    // Open the joystick for reading and store its handle in the joy variable
    SDL_Joystick *joy = SDL_JoystickOpen(0);

    // If the joy variable is NULL, there was an error opening it.
    if (joy != NULL) {
        // Get information about the joystick
        const char *name = SDL_JoystickName(joy);
        const int num_axes = SDL_JoystickNumAxes(joy);
        const int num_buttons = SDL_JoystickNumButtons(joy);
        const int num_hats = SDL_JoystickNumHats(joy);

        printf("Now reading from joystick '%s' with:\n"
               "%d axes\n"
               "%d buttons\n"
               "%d hats\n\n",
               name,
               num_axes,
               num_buttons,
               num_hats);

        //int quit = 0;

        // Keep reading the state of the joystick in a loop
        while (quit == 0) {
            if (SDL_QuitRequested()) {
                quit = 1;
            }

            for (int i = 0; i < num_axes; i++) {
                printf("Axis %d: %d\n", i, SDL_JoystickGetAxis(joy, i)); 
            }

            for (int i = 0; i < num_buttons; i++) {
                printf("Button %d: %d\n", i, SDL_JoystickGetButton(joy, i));
            }

            for (int i = 0; i < num_hats; i++) {
                printf("Hat %d: %d\n", i, SDL_JoystickGetHat(joy, i));
            }

            printf("\n");

            SDL_Delay(50);
        }

        SDL_JoystickClose(joy);
    } else {
        printf("Couldn't open the joystick. Quitting now...\n");
    }

    SDL_Quit();
    return 0;
}
*/

/*
* Constructor.
* Event Engine is the class on top, handles windows.
* And inputs. 
*/


EventEngine::EventEngine(unsigned int fps_): fps(float(fps_))
{

	if (SDL_WasInit(SDL_INIT_VIDEO) == 0) 
	{
	//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			
		}
	}
	
#ifdef OPENGL_MACRO
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
#endif
#ifdef OPENGLES_MACRO
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif	
	keyboard = SDL_GetKeyboardState(NULL);
	
	

	
}

/*
* Start Tracking the state of a Button.
*
*/

void EventEngine::TrackButton(int keycode_)
{
	keyboard_old[keycode_]=keyboard[keycode_];
	alreadyupdatedkeys[keycode_]=false;
	keyboardState[keycode_]=INVALID;
}


/*
* Get the state of a Button.
*
*/


ButtonAction EventEngine::GetState(int keycode_)
{

	std::map<int,Uint8>::iterator it = keyboard_old.find(keycode_);
	std::map<int,bool>::iterator lit = alreadyupdatedkeys.find(keycode_);
	std::map<int,ButtonAction>::iterator itG = keyboardState.find(keycode_);
	if(it ==  keyboard_old.end())
	{
		printf("Error, key not tracked, use EventEngine::TrackButton(int keycode_)\n");
		throw std::exception();
	}
	else if ( !  lit ->second )
	{
		//{ PRESSED = 2 , RELEASED = 1, STEADY_DOWN = 3 , STEADY_UP = 0 };
		itG->second = (ButtonAction) (it->second+2*keyboard[keycode_])  ;
		it->second=keyboard[keycode_];
		lit ->second = true;
	}
	
	return itG->second;
	
	
}

/*
* Start Handling a window 
*
*/


void  EventEngine::HandleWindow(Window_Class* w)
{
	windows[w->IDWindow]= w;
}

/*
* Handle events related to a window 
* To be completed.
*/



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
	//Reset keyboard
	//for (auto& [_, v] : alreadyupdatedkeys) v = false;
	for (auto it = alreadyupdatedkeys.begin();it != alreadyupdatedkeys.end(); it++)
	{
	 	it->second = false;
	}
	
	
	unsigned int now_frame = SDL_GetTicks() - frame_start;
#ifdef SHOWFPS
	std::cout <<  now_frame << "  " << 1000/fps << "  " << ( now_frame  < 1000/fps)  << "\n";
#endif
	if ( now_frame < 1000/fps ) {
#ifdef EMSCRIPTEN_MACRO
		emscripten_sleep(1000/fps - now_frame);
#else
		SDL_Delay(1000/fps - now_frame);
#endif
	}
	frame_start = SDL_GetTicks();
	
		
		
	

}

unsigned int EventEngine::GetTime()
{
	
	return SDL_GetTicks();
}

