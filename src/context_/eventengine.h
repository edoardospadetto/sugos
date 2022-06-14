#ifndef EVENTENGINE
#define EVENTENGINE

#include <map> 
#include "../include/enums.h"
class Window_Class;
class EventEngine
{

	 std::map<int,ButtonAction> keyboardState;
	 std::map<int,Uint8> keyboard_old;
	 std::map<int,bool> alreadyupdatedkeys;
	 
	 float fps = 60 ;
	 unsigned int frame_start = 0; 
	 std::map<int,Window_Class*> windows;
	 public:
	 const Uint8* keyboard;
	 void TrackButton(int keycode_);
	 ButtonAction GetState(int keycode_);
	 EventEngine(unsigned int fps_);
	 void HandleWindow(Window_Class* w);
	 void WindowsEvents();
	 unsigned int GetTime();

};
#endif
