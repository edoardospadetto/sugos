#include "../turtle.h" 


//STBI IMAGE
#ifndef EXTERNAL
#define EXTERNAL 

#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb_image.h"

#endif

/*
* Generate Texture from image, with path filename, flip flips the ordering of the pixel, 
* desiderchannels are the number of channels, color format GL_RGB or GL_RGBA so on. 
*
*/
void Texture::LoadTexture(Window_Class *w, const std::string& filename,bool flip_, int desiredchannels, GLenum colorformat )
{
	
	w->MakeCurrent();
	glGenTextures(1, &( textureId));
	glBindTexture(GL_TEXTURE_2D,  textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(int(flip_));
	unsigned char *data = stbi_load(filename.c_str(), &tx_width, &tx_height, &nrChannels, desiredchannels);
	
	if (data)
	{
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, colorformat, tx_width, tx_height, 0, colorformat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		ltexture = true;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		textureId=-1;

	}
	stbi_image_free(data); 
	glCheckError(); 
	
}

void Texture::LoadTexture(Window_Class *w,std::string&& filename,bool flip_, int desiredchannels, GLenum colorformat)
{
	LoadTexture(w, filename,flip_,desiredchannels,colorformat);
}


void Texture::RenderTexture()
{

	//is this temp?
	if(textureId != -1 )
	{
		glBindTexture(GL_TEXTURE_2D, this->textureId);
		glCheckError();
	}
	else
	{
		printf("ERROR, invalid textureID\n");
		throw std::exception();
	}
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, NULL );
	glCheckError();
}

