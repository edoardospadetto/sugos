

class CollisionEngine
{
	public: 
	float* minOverlap;	
	std::vector<int> collidingObjects;
	std::vector<ColliderObject2D*> collisionSet;
	
	glm::vec2* hitDirection ;
	
	int Ncoll;
	
	
	void UpdateDbgColliders();
	void StartCollisions();
	void HandleCollisions();
	void VerifyCollisions();
	void EndCollisions();
	
	void LoadCollidingObject(ColliderObject2D* tmpObj_);
};


//=======================================================================================
//=================================   Debug   ===========================================
//=======================================================================================

void CollisionEngine::UpdateDbgColliders()
{
	for (auto obj : collisionSet )
	{
	
		obj->collider->colliderRep->SetUniform("c",0,*(obj->collider->xc));
		obj->collider->colliderRep->SetUniform("c",1,*(obj->collider->yc));
		obj->collider->colliderRep->SetUniform("c",2,*(obj->collider->angle));
	}	


}

//=======================================================================================
	

void CollisionEngine::VerifyCollisions()
{

	CollisionStatus coupleStatus;
	//debug
	const char* statuses[] =  { "NOT_COLLIDING" , "COLLIDING", "ON_CHECK" , "TO_CHECK"};
	
	int index = 0;
	
	

	for (int i=1;  i< Ncoll ; i++ )
	{
		//dbglog(i, Ncoll);
		Collider2D *c1 = collisionSet[i]->collider;
	
	for (int j=0;  j< i ;j++ )
	{
	
		coupleStatus=TO_CHECK;
	
		Collider2D *c2 = collisionSet[j]->collider;
		
		index = i*(i-1)/2 +j;
		//dbglog("index ",index);
		/*
		* hit direction positive if c1 colliding towords right.
		* if i<j then 1 else -1, to simmetrize hit direction
		*/ 
		
		c1->Check(c2, coupleStatus, &(hitDirection[index]), &(minOverlap[index]), +1.0 );
		c2->Check(c1, coupleStatus, &(hitDirection[index]), &(minOverlap[index]), -1.0 );
	
		
		
		
		
		if ( coupleStatus == COLLIDING ) collidingObjects.push_back(index);
				
		
	}
	}

}

void CollisionEngine::HandleCollisions()
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
		
		ColliderObject2D *obj1 = collisionSet[row ];
		ColliderObject2D *obj2 = collisionSet[col ];
		
		
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


void CollisionEngine::LoadCollidingObject(ColliderObject2D* tmpObj_)
{
	if(tmpObj_ != nullptr) // Go on with animation temp_obj->Animate();
	{	
		
		if (&(tmpObj_->collider) == nullptr)
		{
			printf("ERROR, collider is not defined\n ");
			throw std::exception();
		} 
		else this->collisionSet.push_back(tmpObj_);
		
	}
	

}

void CollisionEngine::StartCollisions()
{
	Ncoll = collisionSet.size();
	minOverlap = new float[ ((Ncoll)*(Ncoll-1))/2 ];
	hitDirection = new glm::vec2[ ((Ncoll)*(Ncoll-1))/2 ];
}


void CollisionEngine::EndCollisions()
{
	collidingObjects.clear();
	delete [] hitDirection ;
	delete [] minOverlap;
}





