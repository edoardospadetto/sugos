#ifndef COLLISIONENGINE
#define COLLISIONENGINE




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

#endif
