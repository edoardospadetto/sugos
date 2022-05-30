#include "../../turtle.h"

void RigidCollision(std::vector<ColliderObject2D*> &collisionSet, std::vector<int> &collidingObjects, glm::vec2* hitDirection, float* minOverlap )
{

	//TEMP
	
	
	float eps = 0.0001;
	
	
			
	/*
	* colliding objects contains linearized coordinates of a lower triangular matrix without
	* diagonal. To get back the inices of row and column, i.e. the 2 objects we use the following.
	*/
	
	
	for (auto index : collidingObjects)	
	{
		int row =  ceil ((-1 + sqrt(2+8*index) )/2.0 -1 ) +1 ;
	  	int col =  index- ( row*(row-1)/2 )  ;
		
		ColliderObject2D *obj1 = collisionSet[row];

		
		
		glm::vec2 edge{-hitDirection[index].y, hitDirection[index].x};
	
		
		if ( true)//glm::length(velocity)  >= float(1e-10))
		{
			
		
			minOverlap[index]+=eps;
			obj1->position[0] -= minOverlap[index]*hitDirection[index].x;// -  final_move.x;
			obj1->position[1] -= minOverlap[index]*hitDirection[index].y;// -  final_move.y;
			
			
			//dbglog("dir ;", hitDirection[index].x, hitDirection[index].y, "ov " ,  velocity_dir.x,  velocity_dir.y );
		}
		
	}


}
