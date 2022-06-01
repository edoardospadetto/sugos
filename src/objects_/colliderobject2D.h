#ifndef COLLIDEROBJECT2D
#define COLLIDEROBJECT2D

#include <glm/glm.hpp>

#include "../include/enums.h"
#include "../modules_/geometry_module.h"
#include "../objects_/vectorizedobject.h"
class Collider2D;

class  ColliderObject2D  : virtual public VectorizedObject
{
	
	int collisionSetIdx = -1;
	
	public:
	
	
	
	ColliderObject2D(int vertex_len_,int vertex_num_, int surfaces_num_, int space_dim_,GLenum representation_);
	void SameShapeCollider(int vblocation, Polygon shape_);
		
	Collider2D *collider= nullptr; 
	~ColliderObject2D();

	friend class CollisionEngine;

};

#endif
