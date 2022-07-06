#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>


//Problems multiwindow.
//Focus textbox single window
int main()
{
 //std::string font0 = "!\"#$%_'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_'abcdefghiklmnopqrstuvwxyz{|}~ç€£&à";
 //"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?"
  EventEngine MainEngine=EventEngine(60);
  Window_Class menu = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor", 640,320 ); 
  MainEngine.HandleWindow(&menu);
  
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes0=GPUcodes(&menu,"./src/shaders_/font.shader");	
  gpucodes0.Load("fontV","fontF", "font");
  
  Texture fontTexture = Texture();
 
  fontTexture.LoadTexture(&menu,"./etc/fonts/font.png",true,4, GL_RGBA);
  dbglog(fontTexture.tx_width, fontTexture.tx_height );
  //BitmapFont pixelFont =  BitmapFont("ABCD", 2, 2, 16, 16, &fontTexture);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  
  
  Textbox tbtext = Textbox("LIL RUSSIAN", &pixelFont,1,11,0.1,0.2);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(-0.7,-0.2,0.0,0.3);
  tbtext.SetLetterColor(2,1.0,0.0,0.0,1.0);
  tbtext.SetLetterColor(3,0.0,1.0,0.0,1.0);
  tbtext.SetLetterColor(4,0.0,0.0,1.0,1.0);
  tbtext.SetLetterColor(5,1.0,1.0,0.0,1.0);
  
   
	//ANIM
	Texture monkSpriteSheet;
	monkSpriteSheet.LoadTexture(&menu,"./etc/spritesheets/monkspritesheey.png", true, 4, GL_RGBA);

	State run("./etc/animconffiles/monkrun.anim", &monkSpriteSheet), attack("./etc/animconffiles/monkattack.anim", &monkSpriteSheet);
	run.ConnectTo(&attack, SDL_SCANCODE_UP , ON_PRESS);
	attack.ConnectTo(&run, TIME_OUT , UNDEFINED );

	StateEngine monkanim(&MainEngine); 
	monkanim.AddState(&run);
	monkanim.AddState(&attack);
	// Shader
	GPUcodes gpucodes1=GPUcodes(&menu, "./src/shaders_/anim.shader");	

	gpucodes1.Load("texturev","texturef", "simplea");

	glClearColor( 0.f, 0.f, 0.f, 1.f );
		
	AnimatedObject2D MonkChar(4,4,1,2,GL_QUADS,&monkanim);

	GenQuadText(MonkChar);	
	MonkChar.SetToOrigin(0);
	MonkChar.Rescale(0,0.7);
	//MonkChar.SetSnapshot(0, 0);

	MonkChar.LinkUniformToVariable("status", 2);

	MonkChar.SpecifyBuffersAttributes("aPos", 2);	
	MonkChar.SpecifyBuffersAttributes("aTex", 2);

	

	
  
  Scene test = Scene();
  test.LoadObject(&MonkChar, gpucodes1.glprograms[0]);	
  test.LoadObject(&tbtext, gpucodes0.glprograms[0]);	
  test.Prepare();
  //menuscene = Scene()
  std::cout << "MAIN LOOP \n \n"; 
 
  while(menu.IsAlive())
  {     menu.CycleStart();
	test.Prepare();
  	test.Update();
  	//if(kb[SDL_SCANCODE_Q] == 1) quit = true;
  	
	
	menu.CycleEnd();
	MainEngine.WindowsEvents();
  }
  menu.Close();
  
}
