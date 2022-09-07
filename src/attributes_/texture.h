/*
* Texture Class
* It is in interface to the OpenGL Texture object.
* From image. to Gl texture.
* Uses the default constructor and load the image afterwards.
*/

#ifndef TEXTURE
#define TEXTURE
#include "../include/safe_include_SDLGL_OpenGL.h"
#include "../context_/window.h"

class Texture
{
	public:
	
	int tx_width, tx_height; // in pixel
	GLuint textureId=-1;
	bool ltexture = false;
	void LoadTexture(Window_Class *w,const std::string& filename,bool flip_, int desiredchannels, GLenum colorformat );
	void LoadTexture(Window_Class *w,std::string&& filename,bool flip_, int desiredchannels, GLenum colorformat  );
	void LoadTexture(Window_Class *w,float* array, int size1, int size2, int size3);
	void RenderTexture(int idx);
	void UnbindTexture();

};

#endif
