#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>


int main()
{
 
  EventEngine MainEngine=EventEngine(60);
  Window_Class w1 = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor1", 640,320 ); 
  Window_Class w2 = Window_Class(SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor", 640,320 ); 
  MainEngine.HandleWindow(&w1);
  MainEngine.HandleWindow(&w2);
  
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucodes0=GPUcodes(&w1, "./src/shaders_/font.shader");
  gpucodes0.Load("fontV","fontF", "font");
  GPUcodes gpucodes1=GPUcodes(&w2, "./src/shaders_/font.shader");
  gpucodes1.Load("fontV","fontF", "font");
  
  Texture fontTexture1 = Texture();
  Texture fontTexture2 = Texture();
 
  fontTexture1.LoadTexture(&w1, "./etc/fonts/font.png",true,4, GL_RGBA);
  fontTexture2.LoadTexture(&w2, "./etc/fonts/font.png",true,4, GL_RGBA);
 
 
  BitmapFont pixelFont1 =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture1);
  BitmapFont pixelFont2 =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture2);
  
  
  Textbox tbtext = Textbox("LIB", &pixelFont1,1,3,0.1,0.2);
  tbtext.SetUpDefaultShader();
  tbtext.SetCoords(-0.7,-0.2,0.0,0.5);
  tbtext.SetLetterColor(2,1.0,0.0,0.0,1.0);
  tbtext.SetLetterColor(0,0.0,1.0,0.0,1.0);
  
  
  Textbox tbtext3 = Textbox("SUGOS", &pixelFont1,1,5,0.1,0.2);
  tbtext3.SetUpDefaultShader();
  tbtext3.SetCoords(-0.3,-0.2,0.0,0.5);
  tbtext3.SetLetterColor(2,1.0,0.0,1.0,1.0);
  tbtext3.SetLetterColor(0,0.1,0.3,0.7,1.0);
  
  Textbox tbtext4 = Textbox("ROCKS", &pixelFont1,1,5,0.1,0.2);
  tbtext4.SetUpDefaultShader();
  tbtext4.SetCoords(0.2,0.2,0.0,0.5);
  tbtext4.SetLetterColor(2,1.0,0.0,1.0,1.0);
  tbtext4.SetLetterColor(0,1.0,1.0,0.0,1.0);
  tbtext4.SetLetterColor(4,0.0,1.0,1.0,1.0);
  
  Textbox tbtext2 = Textbox("IS     U     G     O     SUPER", &pixelFont2,5,6,0.1,0.2);
  tbtext2.SetUpDefaultShader(); //Make control for warning
  tbtext2.SetCoords(0.3,-0.5,0.0,0.0);
  tbtext2.SetLetterColor(0,1.0,0.0,0.0,1.0);
  tbtext2.SetLetterColor(1,0.0,1.0,0.0,1.0);
  tbtext2.SetLetterColor(25,0.0,0.0,1.0,1.0);
  tbtext2.SetLetterColor(26,1.0,1.0,0.0,1.0);
  tbtext2.SetLetterColor(27,0.0,0.0,1.0,1.0);
  tbtext2.SetLetterColor(28,1.0,1.0,0.0,1.0);
  tbtext2.SetLetterColor(29,0.0,0.0,1.0,1.0);
  
  
  
  
  Scene test = Scene();
  Scene test2 = Scene();
  
  test.LoadObj(tbtext, gpucodes0.glprograms[0]);
  test.LoadObj(tbtext3, gpucodes0.glprograms[0]);
  test.LoadObj(tbtext4, gpucodes0.glprograms[0]);
  test2.LoadObj(tbtext2, gpucodes1.glprograms[0]);		 
  test.Prepare();
  test2.Prepare();
  
  std::cout << "MAIN LOOP \n \n"; 
 
  while(w2.IsAlive() && w1.IsAlive())
  {     w1.CycleStart();
	test.Prepare();
  	test.Update();
	
	w1.CycleEnd();
	w2.CycleStart();
	test2.Prepare();
  	test2.Update();
	w2.CycleEnd();
	MainEngine.WindowsEvents();
  }
  w1.Close();
  w2.Close();
  
}
