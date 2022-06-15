#ifndef COLLISIONENGINE
#define COLLISIONENGINE

#include <functional>
#include <type_traits>
#include <glm/glm.hpp>

#include "../objects_/colliderobject2D.h"

class CollisionEngine
{  
	void (*CollisionHandler)( std::vector<ColliderObject2D*>& ,  std::vector<int>&  , glm::vec2*, float* ) { nullptr };

	public: 
	float* minOverlap;	
	std::vector<int> collidingObjects;
	std::vector<ColliderObject2D*> collisionSet;
	
	glm::vec2* hitDirection ;
	
	int Ncoll;
	
	void UnloadObject(ColliderObject2D *obj);
	void UpdateDbgColliders();
	void StartCollisions();
	void HandleCollisions();
	void VerifyCollisions();
	void EndCollisions();
	void SetCollisionHandler(void (*CollisionHandler_)(std::vector<ColliderObject2D*>& , std::vector<int>&  , glm::vec2*, float* ) );
	std::vector<std::vector<glm::vec2>> LoadCollidersFromFile(const std::string& filename_);
	void LoadCollidingObject(ColliderObject2D* tmpObj_);
};

#endif
