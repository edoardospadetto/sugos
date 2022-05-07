
class  AnimatedObject2D  : virtual public VectorizedObject
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



AnimatedObject2D::AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, StateEngine *selfstateengine_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_), selfStateEngine(selfstateengine_)
{
	
};

