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
  Window_Class menu = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor", 640,640 ); 
  MainEngine.HandleWindow(&menu);
  
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes0=GPUcodes(&menu,"./src/shaders_/font.shader");	
  gpucodes0.Load("fontV","fontF", "font");
  
  Texture fontTexture = Texture();
 
  fontTexture.LoadTexture(&menu,"./etc/fonts/font.png",true,4, GL_RGBA);
  dbglog(fontTexture.tx_width, fontTexture.tx_height );
  //BitmapFont pixelFont =  BitmapFont("ABCD", 2, 2, 16, 16, &fontTexture);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  
  
  Textbox tbtext = Textbox("LIL RUSSIAN", &pixelFont,1,11,0.1,0.1);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(0.0,-0.2,0.0,0.0);
  tbtext.SetLetterColor(2,1.0,0.0,0.0,1.0);
  tbtext.SetLetterColor(3,0.0,1.0,0.0,1.0);
  tbtext.SetLetterColor(4,0.0,0.0,1.0,1.0);
  tbtext.SetLetterColor(5,1.0,1.0,0.0,1.0);
  glCheckError();
  
  
  Scene test = Scene();
  test.LoadObject(&tbtext, gpucodes0.glprograms[0]);	
  test.Prepare();
  //menuscene = Scene()
  std::cout << "MAIN LOOP \n \n"; 
  float theta = 0.0;
  while(menu.IsAlive())
  {     
    menu.CycleStart();
  
    theta += 0.01;
    tbtext.SetUniform("CM",2,theta);
	test.Prepare();
  	test.Update();
  	//if(kb[SDL_SCANCODE_Q] == 1) quit = true;
  	
	
	menu.CycleEnd();
	MainEngine.WindowsEvents();
  }
  menu.Close();
  
}
