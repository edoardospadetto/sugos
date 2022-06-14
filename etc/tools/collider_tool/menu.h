class Menu
{
	public:
	Texture* fontTexture;
	Scene* s;
	Window_Class* w;
	BitmapFont *pixelFont;
	int upstate = 0, downstate=0, hidestate=0, showstate=0;
	std::vector<Textbox*> tbtext ={} ;
	int idx=0;
	const Uint8* kb;
	Menu(Window_Class* w_,Scene* s_);
	int MenuLogic();
	~Menu();
	
};


Menu::Menu(Window_Class* w_,Scene* s_) : s(s_), w(w_)
{

	GPUcodes gpucode=GPUcodes(w, "./src/shaders_/font.shader");
	gpucode.Load("fontV","fontF", "font"); // forgot this one
	fontTexture = new Texture();
	
	fontTexture->LoadTexture(w,"./etc/fonts/font.png",true,4, GL_RGBA);

	pixelFont =  new BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, fontTexture); // check if pointer is dead

	tbtext.push_back(new Textbox("EDITOR MODE", pixelFont,1,11,0.05,0.1));
	tbtext.push_back(new Textbox("GAME MODE", pixelFont,1,9,0.05,0.1));
	tbtext.push_back(new Textbox("CLOSE", pixelFont,1,5,0.05,0.1));


	std::cout <<'loaded\n' ;
	
	for (int i=0; i<tbtext.size(); i++)
	{      
	        tbtext[i]->SetUpDefaultShader(); //dont do that twice
		tbtext[i]->SetCoords(-0.9,0.8-0.2*i,0.0,0.0);
		tbtext[i]->SetColor(1.0,1.0,1.0,1.0);
		s->LoadObj(*(tbtext[i]), gpucode.glprograms[0]);	
	}
	tbtext[0]->SetColor(1.0,1.0,0.0,1.0);
	int idx =0;
	s->Prepare();

  	 

}

int Menu::MenuLogic( )
{	
	 kb = SDL_GetKeyboardState(NULL);
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
  	return idx;
}

Menu::~Menu()
{
	delete fontTexture;
	delete pixelFont;
}
