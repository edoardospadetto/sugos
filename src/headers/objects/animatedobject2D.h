#ifndef ANIMATEDOBJECT2D
#define ANIMATEDOBJECT2D



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


#endif
