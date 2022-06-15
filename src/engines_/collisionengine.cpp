#include <cstdio>
#include <fstream>
#include "./collisionengine.h"
#include "../attributes_/collider.h"
#include "../include/enums.h"


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
std::vector<std::vector<glm::vec2>> CollisionEngine::LoadCollidersFromFile(const std::string& filename_)
{
	std::ifstream infile(filename_);
	std::vector<std::vector<glm::vec2>> colliders;
	int N,n;
	float x,y;
	infile >> N;
	for (int i=0; i<N; i++)
	{
		colliders.push_back({});
		infile >> n;
		for (int j=0; j<n; j++)
		{
			infile >> x >> y;
			colliders[i].push_back(glm::vec2{x,y});
		}
	}
	return colliders;
}	

void CollisionEngine::VerifyCollisions()
{

	CollisionStatus coupleStatus;
	//debug
	//const char* statuses[] =  { "NOT_COLLIDING" , "COLLIDING", "ON_CHECK" , "TO_CHECK"};
	
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

void CollisionEngine::SetCollisionHandler(void (*CollisionHandler_)( std::vector<ColliderObject2D*>&, std::vector<int>& , glm::vec2*, float* ) )
{

	CollisionHandler=CollisionHandler_;

}

void CollisionEngine::HandleCollisions()
{
	if(CollisionHandler != nullptr){
		CollisionHandler(collisionSet, collidingObjects, hitDirection, minOverlap);
	}
	else if( this->collisionSet.size() !=0)
	{

		printf("Error, Collision Handling not set correctly\n");
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
		else 
		{	
			this->collisionSet.push_back(tmpObj_);
			tmpObj_->collisionSetIdx = this->collisionSet.size()-1;
		}
	}
	

}

void CollisionEngine::StartCollisions()
{
	Ncoll = collisionSet.size();
	minOverlap = new float[ ((Ncoll)*(Ncoll-1))/2 ];
	hitDirection = new glm::vec2[ ((Ncoll)*(Ncoll-1))/2 ];
}

void CollisionEngine::UnloadObject(ColliderObject2D *obj)
{
	for (int i= obj->collisionSetIdx+1 ; i< int(this->collisionSet.size()); i++)
	{
		this->collisionSet[i]->collisionSetIdx = i-1;
	}
 	this->collisionSet.erase(this->collisionSet.begin() + obj->collisionSetIdx );
 	
}

void CollisionEngine::EndCollisions()
{
	collidingObjects.clear();
	delete [] hitDirection ;
	delete [] minOverlap;
}





