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



AnimatedObject2D::AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, StateEngine *selfstateengine_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_), selfStateEngine(selfstateengine_)
{
	
};



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class  PhysicsObject2D  : public VectorizedObject
{
	public:
	
	

	
	//S SelfAnimationTree;
	
	PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_ );
	void SameShapeCollider(int vblocation);
		
	Collider2D *collider= nullptr; 
	~PhysicsObject2D();
	/*
	void RightSnapshot();
	void SetSnapshotCoords(float x, float y);
	void SetSnapshotSize(float sizex_, float sizey_);
	void SetSnapshotSizePx(int sizex_, int sizey_);
	void SetSnapshot(int x, int y);
	*/

};

PhysicsObject2D::PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_)
{
	
}


void PhysicsObject2D::SameShapeCollider(int vblocation)
{
	std::vector<glm::vec2> x_;

	for (int i=0; i<vertex_num; i++)
	{
			glm::vec2  tmp_= {vertex_buffer[ i*vertex_len + vblocation ]-position[0],vertex_buffer[ i*vertex_len + vblocation +1]-position[0]};
			x_.push_back(tmp_);
			
	}	
	//printf("size : %d \n", x_.size());
	collider = new Collider2D(std::move( x_ ), GENERIC);
}

PhysicsObject2D::~PhysicsObject2D()
{
	if(collider != nullptr) delete collider;
	delete this;
}

