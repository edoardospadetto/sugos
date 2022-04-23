/*
* Texture Class
* It is in interface to the OpenGL Texture object.
* From image. to Gl texture.
* Uses the default constructor and load the image afterwards.
*/
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


/*
* Generate Texture from image, with path filename, flip flips the ordering of the pixel, 
* desiderchannels are the number of channels, color format GL_RGB or GL_RGBA so on. 
*
*/
void Texture::LoadTexture(const std::string& filename,bool flip_, int desiredchannels, GLenum colorformat )
{
	
	
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
	
}

void Texture::LoadTexture(std::string&& filename,bool flip_, int desiredchannels, GLenum colorformat)
{
	LoadTexture(filename,flip_,desiredchannels,colorformat);
}


void Texture::RenderTexture()
{

	//is this temp?
	if(textureId != -1 )
	{
		glBindTexture(GL_TEXTURE_2D, this->textureId);
	}
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, NULL );
}

