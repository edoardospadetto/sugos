#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <turtle.h>



void MenuLogic(std::vector<Textbox*> &tbtext, int &upstate , int &downstate , int &hidestate,int &showstate,   const Uint8* kb , int &idx  )
{
	if(kb[SDL_SCANCODE_UP]!=upstate | kb[SDL_SCANCODE_DOWN]!=downstate|
	   kb[SDL_SCANCODE_H]!=hidestate| kb[SDL_SCANCODE_S]!=showstate )
  	{
  		upstate=kb[SDL_SCANCODE_UP];
  		downstate=kb[SDL_SCANCODE_DOWN];
  		hidestate=kb[SDL_SCANCODE_H];
  		showstate=kb[SDL_SCANCODE_S];
  		tbtext[idx]->SetColor(1.0,1.0,1.0,1.0);
  		if(upstate==1)
  		{
  			idx-=1;
  			if(idx<0) idx = tbtext.size()-1;		
  		}
  		else if (downstate == 1)
  		{
  			idx+=1;
  			if(idx>=tbtext.size()) idx = 0;
  		
  		}
  		else if (hidestate==1)
  		{
			tbtext[idx]->Hide();  		
  		}
  		else if (showstate==1)
  		{
			tbtext[idx]->Show();  	
			std::cout << "SHOW\n" ;	
  		}

  		tbtext[idx]->SetColor(1.0,1.0,0.0,1.0);
  		
  	}
}
float yb = 0.0;
bool widing = false;
float xb=0.0;

void EditCollider(MouseButton  press, float x, float y, std::vector<VectorizedObject*> &squares, Scene *real, GPUcodes* code )
{
	

	
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	
	std::cout << press <<"  press \n"; 
	if (!widing&& press==1)
	{
		widing = true;
		std::cout << "in1\n"; 
		xb=x;
		yb=y;
		
	}
	if(widing && press==0)
	{
		std::cout << "in2\n";
		squares.push_back(new VectorizedObject(6,4,1,2,GL_QUADS));
		GenColorQuad(*squares[squares.size()-1],xb,yb,x,y);
		squares[squares.size()-1]->SpecifyBuffersAttributes("r_", 2) ;
		squares[squares.size()-1]->SpecifyBuffersAttributes("c_", 4) ;
		squares[squares.size()-1]->LinkUniformToVariable("CM", 4);
		real->LoadObj(*squares[squares.size()-1], code->glprograms[0]);
		real->Prepare();	
		widing=false;
	
	}
}
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

  
  std::string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?";
  GPUcodes gpucode=GPUcodes(&w1, "./shaders/font.shader");
 
  Texture fontTexture = Texture();
  fontTexture.LoadTexture(&w1,"./data/fonts/font.png",true,4, GL_RGBA);
 
  gpucode.Load("fontV","fontF", "font1");
  
  BitmapFont pixelFont =  BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, &fontTexture);

  Scene test = Scene();
  
  // MENU
  std::vector<Textbox*> tbtext ={} ;
  tbtext.push_back(new Textbox("EDITOR MODE", &pixelFont,1,11,0.05,0.1));
  tbtext.push_back(new Textbox("GAME MODE", &pixelFont,1,9,0.05,0.1));
  std::cout <<'loaded\n' ;
  tbtext[0]->SetUpDefaultShader();
  tbtext[1]->SetUpDefaultShader();
  for (int i=0; i<tbtext.size(); i++)
  {
  	tbtext[i]->SetCoords(-0.9,0.8-0.2*i,0.0,0.0);
  	tbtext[i]->SetColor(1.0,1.0,1.0,1.0);
  	test.LoadObj(*(tbtext[i]), gpucode.glprograms[0]);	
  }
  tbtext[0]->SetColor(1.0,1.0,0.0,1.0);
  int idx =0;
  test.Prepare();
  //-----------------------------
  
  //OBJECTS
  std::vector<VectorizedObject*> squares ={} ;
  Scene real = Scene();
  GPUcodes vrend=GPUcodes(&w2,"./shaders/vectorizedobject.shader");	
  vrend.Load("vecv","vecf", "vv");
  
  

  std::cout << "MAIN LOOP \n \n"; 
 
  const Uint8* kb = SDL_GetKeyboardState(NULL);
  int upstate = 0, downstate=0, hidestate=0, showstate=0;
  float x,y;
  while(w1.IsAlive() & w2.IsAlive())
  {	
  	   
  	   MenuLogic(tbtext, upstate , downstate , hidestate,showstate, kb, idx  );
  	  
  	   uint a = w2.GetMousePosition(x, y);
  	   std::cout << "mouse in 1,2 " <<  w1.mouseInside << " " << w2.mouseInside << "\n"; 
  	
  	   EditCollider( (MouseButton) a,  x,  y, squares, &real, &vrend );
  
  	   
   	   w1.CycleStart();
  	   test.Prepare();
  	   test.Update();
  	   w1.CycleEnd();
  	   
  	   
  
          w2.CycleStart();
          real.Prepare();
  	  real.Update();
	  w2.CycleEnd();
	 
	 MainEngine.WindowsEvents();
  
  }
  w1.Close();
  w2.Close();
  
   for (int i=0; i<tbtext.size(); i++)
  {
  	delete tbtext[i];
  }
  
}
