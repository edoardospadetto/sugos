//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class  PhysicsObject2D  : virtual public VectorizedObject
{
	public:
	
	

	
	//S SelfAnimationTree;
	
	PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_ );
	void SameShapeCollider(int vblocation, Polygon shape_);
		
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


void PhysicsObject2D::SameShapeCollider(int vblocation, Polygon shape_)
{
	std::vector<glm::vec2> x_;

	for (int i=0; i<vertex_num; i++)
	{
			glm::vec2  tmp_= {vertex_buffer[ i*vertex_len + vblocation ]-position[0],vertex_buffer[ i*vertex_len + vblocation +1]-position[0]};
			x_.push_back(tmp_);
			
	}	
	//printf("size : %d \n", x_.size());
	collider = new Collider2D(std::move( x_ ), shape_);
}

PhysicsObject2D::~PhysicsObject2D()
{
	if(collider != nullptr) delete collider;	
}
