#ifndef COLLIDEROBJECT2D
#define COLLIDEROBJECT2D



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class  ColliderObject2D  : virtual public VectorizedObject
{
	public:
	
	

	
	//S SelfAnimationTree;
	
	ColliderObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_ );
	void SameShapeCollider(int vblocation, Polygon shape_);
		
	Collider2D *collider= nullptr; 
	~ColliderObject2D();
	/*
	void RightSnapshot();
	void SetSnapshotCoords(float x, float y);
	void SetSnapshotSize(float sizex_, float sizey_);
	void SetSnapshotSizePx(int sizex_, int sizey_);
	void SetSnapshot(int x, int y);
	*/

};

#endif
