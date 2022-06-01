
#include "./pngtablefont.h"


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

