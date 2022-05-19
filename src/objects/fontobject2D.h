//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//TexturedObject2D 

/* 
* It is a square, mandatory vbo of a square with 2d texture coordinates.
*  Uniform not mandatory but you would not be able to run animations if not using 
*  a 2d vector to change the texture snapshots. 
*/




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


BitmapFont::BitmapFont(std::string&& characters_, int row_, int col_, int wpx_, int hpx_, Texture *texture_): 
	wpx(wpx_),
	hpx(hpx_),
	row(row_),
	col(col_),
	texture(texture_),
	characters(characters_)
{
// ROW and COL are integer coordinates in the spritesheet
//improper use of vecotors as container of one single element	

	
	
	w  = 1.0/float(col_);//float(texture->tx_width)/float(hpx_);
	h  = 1.0/float(row_);//float(texture->tx_height)/float(wpx_);
	
	/*if(texture->tx_width%wpx_ | texture->tx_height%hpx_ )
	{
		printf("ERROR,  texture has off bounds with respects the character rect: Texture size {%d, %d}, rect size {%d , %d} %d %d \n",
				 texture->tx_width,  texture->tx_height, wpx_, hpx_,  texture->tx_width%wpx_, texture->tx_height%hpx_ );
		throw std::exception();
	}*/
	
	for (int i = 0; i<row*col ; i++ )
	{
		
		char c = characters[i];
		if(c!= ' ')
		{
			int ir= i/col_ , ic=  i%col_;
			coordinates[c]= glm::vec2(ic,ir); //x,y
		}
	}
	coordinates[' ']=  glm::vec2(0,0);
}

class  Textbox : public VectorizedObject
{
	private:
		bool lEnabledShader = false;
	
	public: 
		Textbox(std::string && text_, BitmapFont* font_,  int row_, int col_, float dimx_, float dimy_);
		void EnableShader();
		void SetCoords(float x_,float y_, float z_, float theta_);
		void SetLetterColor(int idx_, float r_, float g_, float b_, float a_ );
		int trow, tcol;
		float x,y;
		float tdimx, tdimy;
		BitmapFont* font;
		//void RenderTexture() ;
		
		
	
};

// 8 vtlen 
Textbox::Textbox(std::string && text_, BitmapFont* font_,  int row_, int col_, float cdimx_, float cdimy_):
VectorizedObject(8,4*row_*col_,row_*col_,2,GL_QUADS),
font(font_),
trow(row_),
tcol(col_),
tdimx(col_*cdimx_),
tdimy(row_*cdimy_),
x(0.0),
y(0.0)
{

	
	 if( trow*tcol != text_.length() ) 
	 {
	 	throw std::exception();
	 }
			
			
	float cdimx = cdimx_; 
	float cdimy = cdimy_;
	for (int i=0; i<(trow*tcol) ; i++) //iterate on char
	{
		char c = text_[i];
		//top left top right bottom left bottom right
		int idxr = trow-1-i/(tcol);
		int idxc = i%(tcol);
		//dbglog( "length ",  text_.length(), idxc, idxr ,font->coordinates[c].x, font->coordinates[c].y );
		//GenQuadText(*this);	
		for (int j=0; j<4; j++) //iterate on vertices of char
		{
				
				int jy= j/2, jx =  abs(abs( (j*2 -3)/2 )-1); //j%2
				this->vertex_buffer[4*8*i+8*j+0] = (idxc+jx)*cdimx;
				this->vertex_buffer[4*8*i+8*j+1] = (idxr+jy )*cdimy;
				this->vertex_buffer[4*8*i+8*j+2] = (font->coordinates[c].x+jx)*font->w;
				this->vertex_buffer[4*8*i+8*j+3] = (font->row - 1 - font->coordinates[c].y+jy)*font->h;
				this->vertex_buffer[4*8*i+8*j+4] = 1.0;
				this->vertex_buffer[4*8*i+8*j+5] = 1.0;
				this->vertex_buffer[4*8*i+8*j+6] = 1.0;
				this->vertex_buffer[4*8*i+8*j+7] = 1.0;
				this->index_buffer[4*i+j] = 4*i+j;
				if (c==' ')
				{
				this->vertex_buffer[4*8*i+8*j+2] =0.0;
				this->vertex_buffer[4*8*i+8*j+3] =0.0;
				}
				/*
				
				dbglog (
				this->vertex_buffer[16*i+4*j+0],
				this->vertex_buffer[16*i+4*j+1]);
				dbglog(
				this->vertex_buffer[16*i+4*j+2],
				this->vertex_buffer[16*i+4*j+3],
				 "\n ---" );
				*/
				
		}	
	}
	//
	

}


void Textbox::EnableShader()
{

	  lEnabledShader=true;
	  this->LinkUniformToVariable("CM", 4);
	  this->SpecifyBuffersAttributes("aPos", 2) ;
	  this->SpecifyBuffersAttributes("aTex", 2) ;
	  this->SpecifyBuffersAttributes("aColor", 4) ;
	  this->SetUniform("CM",0,0.0);
	  this->SetUniform("CM",1,0.0);
	  this->SetUniform("CM",2,0.0);
	  this->SetUniform("CM",3,0.0);
	
}


void Textbox::SetCoords(float x_,float y_, float z_, float theta_)
{
	 if (!lEnabledShader) dbglog("Warning, You can use this with the default shader taht has to be enabled first");
	 this->SetUniform("CM",0,x_);
	 this->SetUniform("CM",1,y_);
	 this->SetUniform("CM",2,theta_);
	 this->SetUniform("CM",3,z_);

}
 
 
void Textbox::SetLetterColor(int idx_, float r_, float g_, float b_, float a_ )
{
	if (!lEnabledShader) dbglog("Warning, You can use this with the default shader taht has to be enabled first");
	for (int j=0; j<4; j++)
	{
		this->vertex_buffer[4*8*idx_+8*j+4] = r_;
		this->vertex_buffer[4*8*idx_+8*j+5] = g_;
		this->vertex_buffer[4*8*idx_+8*j+6] = b_;
		this->vertex_buffer[4*8*idx_+8*j+7] = a_;
	}
	
}
/*void Textbox::RenderTexture()
{
	font->texture->RenderTexture();
}*/

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%







