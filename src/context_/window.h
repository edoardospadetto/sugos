#ifndef WINDOWCLASS
#define WINDOWCLASS

#include <iostream>
#include <SDL2/SDL.h>

class EventEngine;

class Window_Class

{


	
		  SDL_Window* gWindow = NULL;
		  SDL_Surface* screenSurface = NULL;
		  SDL_DisplayMode DM;
		  SDL_GLContext  GLcontext;
		  int IDWindow; 
			
		  //Screen dimension constants
		  int WIDTH = 640;
		  int HEIGHT = 640;
		  
	
		
		  
		  bool lpixelart   = true;
		  bool lmainWindow = false; 
		

		  // state vars 
		   
     private:  
     		
     		float mouseX=0;
     		float mouseY=0;
     		
		bool exit = false; 
		//void WindowEvents();
		void SDLQueue();
		void GLQueue();
		
		bool lresize=false;
		void Resize();
		
		
		 

         public :	
		  bool mouseInside=false;
		 
		  Window_Class(Uint32 flags,  std::string && name);
		  Window_Class(Uint32 flags, std::string && name, int width_, int height_);
		  ~Window_Class();
		  unsigned int GetTime();
		  bool IsAlive();
		  void CycleStart();
		  void MakeCurrent();
		  Uint32 GetMousePosition(float &x, float&y);
		  
		 

		  void Close();
		  int CycleEnd();
		  void SetMainWindow();
		  
		  friend class EventEngine;
		  




};

#endif
