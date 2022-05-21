#ifndef WINDOWCLASS
#define WINDOWCLASS


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

#endif
