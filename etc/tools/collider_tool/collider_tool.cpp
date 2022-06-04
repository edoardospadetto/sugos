#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>
#include "menu.h"
#include "collider_conf.h"



float yb = 0.0;
bool widing = false;
float xb=0.0;


//Problems multiwindow.
//Focus textbox single window
int main()
{
 //std::string font0 = "!\"#$%_'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_'abcdefghiklmnopqrstuvwxyz{|}~ç€£&à";
 //"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?"
  EventEngine MainEngine=EventEngine(60);

  Window_Class w2 = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "win2", 640,320 ); 
  Window_Class w1 = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "win1", 640,320 ); 

  MainEngine.HandleWindow(&w1);
  MainEngine.HandleWindow(&w2);


  Scene menuscene1 = Scene();
  Scene drawscene2 = Scene();
  
  Menu toolmenu=Menu(&w1,&menuscene1);
  ColliderConf conf =  ColliderConf(&w2, &drawscene2);

  //-----------------------------
  
  

  std::cout << "MAIN LOOP \n \n"; 
 
  const Uint8* kb = SDL_GetKeyboardState(NULL);
  int upstate = 0, downstate=0, hidestate=0, showstate=0;
  float x,y;
  while(w1.IsAlive() & w2.IsAlive())
  {	
  	   
  	   toolmenu.MenuLogic();
  	   //MenuLogic(tbtext, upstate , downstate , hidestate,showstate, kb, idx  );
  	  
  	   uint a = w2.GetMousePosition(x, y);
  	   conf.EditCollider( (MouseButton) a,  x,  y);
  	   //std::cout << "mouse in 1,2 " <<  w1.mouseInside << " " << w2.mouseInside << "\n"; 
  	
  	   //EditCollider( (MouseButton) a,  x,  y, squares, &real, &vrend );
  
  	   
   	   w1.CycleStart();
  	   menuscene1.Prepare();
  	   menuscene1.Update();
  	   w1.CycleEnd();
  	   
  	   
  
          w2.CycleStart();
          drawscene2.Prepare();
  	  drawscene2.Update();
	  w2.CycleEnd();
	 
	 MainEngine.WindowsEvents();
  
  }
  w1.Close();
  w2.Close();
  

  
}
