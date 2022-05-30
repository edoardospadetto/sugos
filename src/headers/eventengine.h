#include <map> 

#ifndef EVENTENGINE
#define EVENTENGINE
class Window_Class;
class EventEngine
{
	 float fps = 60 ;
	 unsigned int frame_start = 0; 
	 std::map<int,Window_Class*> windows;
	 public:
	 EventEngine(unsigned int fps_);
	 void HandleWindow(Window_Class* w);
	 void WindowsEvents();

};
#endif
