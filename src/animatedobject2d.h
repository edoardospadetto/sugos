//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//TexturedObject2D 

/* 
* It is a square, mandatory vbo of a square with 2d texture coordinates.
*  Uniform not mandatory but you would not be able to run animations if not using 
*  a 2d vector to change the texture snapshots. 
*/

class  TexturedObject2D  : public VectorizedObject, public Texture
{
	public:
		
	TexturedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_);
	
};



TexturedObject2D::TexturedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_) : VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_)
{
};




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



class  AnimatedObject2D  : public VectorizedObject
{
	public:
	
	

	
	//S SelfAnimationTree;
	
	AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_,StateEngine *selfstateengine_ );
	StateEngine *selfStateEngine;	
	/*
	void RightSnapshot();
	void SetSnapshotCoords(float x, float y);
	void SetSnapshotSize(float sizex_, float sizey_);
	void SetSnapshotSizePx(int sizex_, int sizey_);
	void SetSnapshot(int x, int y);
	*/

};

// Coordinates in integer idx after specifying height and width.




/*
void AnimatedObject2D::SetSnapshotCoords(float x, float y)
{
	if( x > 1.0 | x > 1.0 | y < 0.0 | y > 0.0) printf("Error : OpenGL Texture sizes ranges from 0.0 to 1.0");
}
*/

AnimatedObject2D::AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, StateEngine *selfstateengine_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_), selfStateEngine(selfstateengine_)
{
	
};
