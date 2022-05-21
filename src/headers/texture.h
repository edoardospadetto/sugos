/*
* Texture Class
* It is in interface to the OpenGL Texture object.
* From image. to Gl texture.
* Uses the default constructor and load the image afterwards.
*/

#ifndef TEXTURE
#define TEXTURE
class Texture
{
	public:
	
	int tx_width, tx_height; // in pixel
	GLuint textureId=-1;
	bool ltexture = false;
	void LoadTexture(const std::string& filename,bool flip_, int desiredchannels, GLenum colorformat );
	void LoadTexture(std::string&& filename,bool flip_, int desiredchannels, GLenum colorformat  );
	void RenderTexture();
	void UnbindTexture();

};

#endif
