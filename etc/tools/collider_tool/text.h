class Interface
{
	public:
		BitmapFont *pixelFont=nullptr;
		Texture *fontTexture =nullptr;
		std::vector<Textbox*> tbtext ={} ;
		Interface(Window_Class* w_,Scene* s_);
		void Logic(bool a, bool b, bool c);
		~Interface();
};

Interface::Interface(Window_Class* w_,Scene* s_)
{

	GPUcodes gpucode=GPUcodes(w_, "./src/shaders_/font.shader");
	gpucode.Load("fontV","fontF", "font"); // forgot this one
	fontTexture = new Texture();
	
	fontTexture->LoadTexture(w_,"./etc/fonts/font.png",true,4, GL_RGBA);

	pixelFont =  new BitmapFont("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,!?", 5, 8, 8, 10, fontTexture); // check if pointer is dead

	tbtext.push_back(new Textbox("CLOSE SHAPE", pixelFont,1,11,0.03,0.05));
	tbtext.push_back(new Textbox("NEXT FRAME", pixelFont,1,10,0.03,0.05));
	tbtext.push_back(new Textbox("SAVE COLLIDERS", pixelFont,1,14,0.03,0.05));
	
	
	for (int i=0; i<tbtext.size(); i++)
	{      
		tbtext[i]->SetUpDefaultShader(); //dont do that twice
		tbtext[i]->SetCoords(-0.9,0.8-0.15*i,0.0,0.0);
		tbtext[i]->SetColor(1.0,1.0,1.0,1.0);
		s_->LoadObj(*(tbtext[i]), gpucode.glprograms[0]);	
	}
	s_->Prepare();

}

void Interface::Logic(bool c, bool n, bool s)
{
	for (int idx=0; idx<this->tbtext.size(); idx++)
	{
		tbtext[idx]->SetColor(1.0,1.0,1.0,1.0);
	}	
	if (c) tbtext[0]->SetColor(1.0,1.0,0.0,1.0);
	if (n) tbtext[1]->SetColor(1.0,1.0,0.0,1.0);
	if (s) tbtext[2]->SetColor(1.0,1.0,0.0,1.0);
}	

Interface::~Interface()
{
	delete fontTexture;
	delete pixelFont;
}


