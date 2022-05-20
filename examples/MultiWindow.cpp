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
 

 

  Window_Class w1 = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor1", 640,320 ); 
  Window_Class w2 = Window_Class(60,SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN, "Editor", 640,320 ); 
  w2.SetMainWindow();
  //w2.IsChildOf(&w1);

  
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  
  GPUcodes gpucodes0=GPUcodes(&w1, "./shaders/font.shader");

  gpucodes0.Load("fontV","fontF", "font");
  
  Texture fontTexture = Texture();
 
  fontTexture.LoadTexture("./data/fonts/font.png",true,4, GL_RGBA);
  dbglog(fontTexture.tx_width, fontTexture.tx_height );
  //BitmapFont pixelFont =  BitmapFont("ABCD", 2, 2, 16, 16, &fontTexture);
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);
  
  
  Textbox tbtext = Textbox("LIL RUSSIAN", &pixelFont,1,11,0.1,0.2);
  tbtext.EnableShader();
  tbtext.SetCoords(-0.7,-0.2,0.0,0.3);
  tbtext.SetLetterColor(2,1.0,0.0,0.0,1.0);
  tbtext.SetLetterColor(3,0.0,1.0,0.0,1.0);
  tbtext.SetLetterColor(4,0.0,0.0,1.0,1.0);
  tbtext.SetLetterColor(5,1.0,1.0,0.0,1.0);
  
  
  
  Scene test = Scene(&w1);
  
  test.LoadObj(tbtext, gpucodes0.glprograms[0]);	 
  test.Prepare();

  std::cout << "MAIN LOOP \n \n"; 
 
  while(w2.IsAlive())
  {     w1.CycleStart();
	test.Prepare();
  	test.Update();
	w1.CycleEnd();
	w2.CycleStart();
	w2.CycleEnd();
  }
  w1.Close();
  w2.Close();
  
}
