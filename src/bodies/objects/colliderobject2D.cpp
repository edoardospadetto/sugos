#include "../../turtle.h"

ColliderObject2D::ColliderObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_)
{
	
}


void ColliderObject2D::SameShapeCollider(int vblocation, Polygon shape_)
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

ColliderObject2D::~ColliderObject2D()
{
	if(collider != nullptr) delete collider;	
}
