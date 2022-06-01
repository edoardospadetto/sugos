/*

class glBitmapWriter : public Texture;
{
	public: 
		Texture* texture;
		std::vector<FontObject2D> characters;
		std::map<char,glm::vec2> coordinates;
};
*/
/*
* Character string is in row major format.
* Texture should be ready when put as input
*/
/*
glBitmapWriter(std::string && chars_, int row_ , int col_, Texture* texture_): texture(texture_)
{
	
	for (int i = 0; i<row_*col_ ; i++ )
	{
		char c = chars_[i];
		int ir= i/row_ , ic= i%row_;
		coordinates[c]= glm::vec2(ir,ic);
		characters.push_back(FontObject2D( row_, col_, wpx_, hpx_, texture_));
	}
}	

glBitmapWriter::textbox(std::string && text_, float x_, float y_, float w_, float h_, int row_ , int col_ )
{
	if()

}
*/

*/
/*

void WindowText::LoadFont(SDL_Renderer *renderer, std::string && file)
{


    
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (surface) {
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    //SDL_Delay(2000);
   

}

*/
/*
void WindowText::Print()
{



}
*/
/*
void SDLprint(widow)
{


}
*/
