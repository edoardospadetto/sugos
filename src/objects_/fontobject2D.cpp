#include "./fontobject2D.h"
#include "../modules_/debugmisc_module.h"
#include "../attributes_/pngtablefont.h"


/*
* Textbox is a basic implementation of text rendering. String to be printed needs to be given as input. 
* font is the font object to be used. Rows and columns represent the number of lines and characters per 
* line and their product need to be equal to the length of the string. last parameter involves the 
* dimensions of each charater, width and height. 
*
* This implementation relyes on treating each character as a rectangle (2 triangles) which is used 
* to render the texture related to the corresponding letter. 
*/

Textbox::Textbox(std::string && text_, BitmapFont* font_,  int row_, int col_, float cdimx_, float cdimy_):
VectorizedObject(8,4*row_*col_,2*row_*col_,2,GL_TRIANGLES),
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
	 	std::cout << "Size of text different than size of grid\n" ;
	 	throw std::exception();
	 }
			
			
	float cdimx = cdimx_; 
	float cdimy = cdimy_;
	for (int i=0; i<(trow*tcol) ; i++) //iterate on char
	{
		char c = text_[i];
		//iteration sequence:
		//top left, top right, bottom left, bottom right
		int idxr = trow-1-i/(tcol);
		int idxc = i%(tcol);
		
		for (int j=0; j<4; j++) //iterate on vertices of char
		{
				
				int jy= j/2, jx =  abs(abs( (j*2 -3)/2 )-1); //j%2
				this->vertex_buffer[4*8*i+8*j+0] = (idxc+jx)*cdimx;
				this->vertex_buffer[4*8*i+8*j+1] = (idxr+jy)*cdimy;
				this->vertex_buffer[4*8*i+8*j+2] = (font->coordinates[c].x+jx)*font->w;
				this->vertex_buffer[4*8*i+8*j+3] = (font->row - 1 - font->coordinates[c].y+jy)*font->h;
				this->vertex_buffer[4*8*i+8*j+4] = 1.0;
				this->vertex_buffer[4*8*i+8*j+5] = 1.0;
				this->vertex_buffer[4*8*i+8*j+6] = 1.0;
				this->vertex_buffer[4*8*i+8*j+7] = 1.0;
				
				if (c==' ')
				{
				this->vertex_buffer[4*8*i+8*j+2] =0.0;
				this->vertex_buffer[4*8*i+8*j+3] =0.0;
				}
				
				
		}
		//iterate on index buffer
		
		this->index_buffer[6*i+0] = 4*i+0;
		this->index_buffer[6*i+1] = 4*i+1;
		this->index_buffer[6*i+2] = 4*i+2;
		this->index_buffer[6*i+3] = 4*i+0;
		this->index_buffer[6*i+4] = 4*i+2;
		this->index_buffer[6*i+5] = 4*i+3;
		
		
	}
}

void Textbox::SetColor(float r_, float g_,  float b_, float a_ )
{
	for (int i=0; i<trow*tcol; i++)
	{
		SetLetterColor(i, r_, g_, b_, a_ );
	}
}


void Textbox::SetUpDefaultShader()
{

	  lEnabledShader=true;
	  this->LinkUniformToVariable("CM", 4, GL_FLOAT);
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
	 if (!lEnabledShader) dbglog("Warning, You can use this with the default shader that has to be enabled first");
	 this->SetUniform("CM",0,x_);
	 this->SetUniform("CM",1,y_);
	 this->SetUniform("CM",2,theta_);
	 this->SetUniform("CM",3,z_);

}
 
 
void Textbox::SetLetterColor(int idx_, float r_, float g_, float b_, float a_ )
{
	if (!lEnabledShader) dbglog("Warning, You can use this with the default shader that has to be enabled first");
	for (int j=0; j<4; j++)
	{
		this->vertex_buffer[4*8*idx_+8*j+4] = r_;
		this->vertex_buffer[4*8*idx_+8*j+5] = g_;
		this->vertex_buffer[4*8*idx_+8*j+6] = b_;
		this->vertex_buffer[4*8*idx_+8*j+7] = a_;
	}
	
}
void Textbox::RenderTexture()
{
	font->texture->RenderTexture(0);
}
void Textbox::UnbindTexture()
{
	font->texture->UnbindTexture();
}





