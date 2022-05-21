#ifndef TEXTBOX
#define TEXTBOX




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

#endif
