#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>
#include "text.h"
#include "collider_conf.h"



float yb = 0.0;
bool widing = false;
float xb=0.0;


//Problems multiwindow.
//Focus textbox single window
int main()
{

  std::string name0="runcolliders";
  //std::cin>>name0;
  EventEngine MainEngine=EventEngine(60);

  Window_Class w2 = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "win2", 640,320 ); 
  MainEngine.HandleWindow(&w2);
  Scene drawscene2 = Scene();

  //-----------------------------
  Texture monkSpriteSheet;
  monkSpriteSheet.LoadTexture(&w2,"./etc/spritesheets/monkspritesheey.png", true, 4, GL_RGBA);
  State run("./etc/animconffiles/monkrun.anim", &monkSpriteSheet);

  
  StateEngine monkanim(&MainEngine); 
  monkanim.AddState(&run);
  run.ConnectTo(&run, TIME_OUT , UNDEFINED );
  GPUcodes gpucodes0=GPUcodes(&w2, "./src/shaders_/anim.shader");	

  gpucodes0.Load("texturev","texturef", "simplea");
	
 
  AnimatedObject2D MonkChar(4,4,1,2,GL_QUADS,&monkanim);
  
  GenQuadText(MonkChar);	
  MonkChar.SetToOrigin(0);
  MonkChar.Rescale(0,0.7);
  //MonkChar.SetSnapshot(0, 0);

  MonkChar.LinkUniformToVariable("status", 2);

  MonkChar.SpecifyBuffersAttributes("aPos", 2);	
  MonkChar.SpecifyBuffersAttributes("aTex", 2);

 
  drawscene2.LoadObj(MonkChar, gpucodes0.glprograms[0]);	
  drawscene2.Prepare();

  ColliderConf conf =  ColliderConf(&w2, &drawscene2, name0);
  Interface interface2(&w2,&drawscene2);
  monkanim.TriggerFrameChangeOnKeyPress(SDL_SCANCODE_RIGHT);
  
  std::cout << "MAIN LOOP \n \n"; 
 
  const Uint8* kb = SDL_GetKeyboardState(NULL);
  float x,y;
  MainEngine.TrackButton(SDL_SCANCODE_C);
  MainEngine.TrackButton(SDL_SCANCODE_S);
  MainEngine.TrackButton(SDL_SCANCODE_RIGHT);
  //MainEngine.TrackButton(SDL_SCANCODE_LEFT);
  bool c,n,s;
  bool c1,n1,s1;
  
  conf.AddCollider();
  
  while( w2.IsAlive())
  {	
  	   
  

	uint a = w2.GetMousePosition(x, y);
	
	c = MainEngine.GetState(SDL_SCANCODE_C) == PRESSED;
	s = MainEngine.GetState(SDL_SCANCODE_S) == PRESSED;
	n = MainEngine.GetState(SDL_SCANCODE_RIGHT) == PRESSED;
	//p =  MainEngine.GetState(SDL_SCANCODE_LEFT) == PRESSED;
	
	c1 = (MainEngine.GetState(SDL_SCANCODE_C) == STEADY_DOWN) | c;
	s1 = (MainEngine.GetState(SDL_SCANCODE_S) == STEADY_DOWN) | s;
	n1 = (MainEngine.GetState(SDL_SCANCODE_RIGHT) == STEADY_DOWN) | n;
	//p1 = (MainEngine.GetState(SDL_SCANCODE_LEFT) == STEADY_DOWN) | n;
	//std::cout << c1 << s1 << n1 << "\n"; 
	interface2.Logic(c1,n1,s1);
	
	w2.CycleStart();
	drawscene2.Prepare();
	drawscene2.Update();
	w2.CycleEnd();
	
	if (c) conf.Close();
	else if  (s) conf.SaveCoords();
	else if  (n)
	{
		if(MonkChar.HasAnimationRestarted()) conf.SetCollider(0);
		else conf.MoveCollider(+1);
	} 
	
	//else if  (p) {conf.MoveCollider(-1);}
	else conf.EditCollider( (MouseButton) a,  x,  y);
	
		
	 
	MainEngine.WindowsEvents();
	c=0;
	s=0;
	n=0;
	c1=0;
	s1=0;
	n1=0;
  
  }
  w2.Close();
  

  
}
