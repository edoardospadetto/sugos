#include "colliderobject2D.h"

#include "../attributes_/collider.h"
ColliderObject2D::ColliderObject2D(int vertex_len_,int vertex_num_, int surfaces_num_, int space_dim_,GLenum representation_) : 
VectorizedObject(vertex_len_,vertex_num_,surfaces_num_,space_dim_,representation_)
{
	
}

/*
* Constructs collider object from vertex buffer. vblocation represent the first index of a 2D coordinate point, in the vertex buffer.
* Coordinates are assumed contiguos. Shape of the collider has to be specified.  
*/
void ColliderObject2D::SameShapeCollider(int vblocation, Polygon shape_)
{
	std::vector<glm::vec2> x_;

	for (int i=0; i<vertex_num; i++)
	{
			glm::vec2  tmp_= {vertex_buffer[ i*vertex_len + vblocation ]-position[0],vertex_buffer[ i*vertex_len + vblocation +1]-position[0]};
			x_.push_back(tmp_);
			
	}	
	collider = new Collider2D(std::move( x_ ), shape_);
}

ColliderObject2D::~ColliderObject2D()
{
	if(collider != nullptr) delete collider;	
}
