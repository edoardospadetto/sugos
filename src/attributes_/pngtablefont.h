//TexturedObject2D 

/* 
* It is a square, mandatory vbo of a square with 2d texture coordinates.
*  Uniform not mandatory but you would not be able to run animations if not using 
*  a 2d vector to change the texture snapshots. 
*/


#ifndef FONTS
#define FONTS

#include<map>
#include<string>
#include "../include/glm.h"
#include "../include/SDL&OpenGL.h"
#include "../context_/window.h"
#include "../attributes_/texture.h"

struct BitmapFont
{

	
	BitmapFont(std::string&& characters_, int row_, int col_, int wpx_, int hpx_, Texture *texture_);
	std::map<char,glm::vec2> coordinates;
	std::string characters;
	int row;
	int col;
	int wpx;
	int hpx;
	float w; // size of letter
	float h;
	Texture* texture;

};



#endif
