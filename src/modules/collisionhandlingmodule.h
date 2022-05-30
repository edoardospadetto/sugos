#ifndef COLLISIONHANDLING
#define COLLISIONHANDLING
void RigidCollision(std::vector<ColliderObject2D*> &collisionSet , std::vector<int> &collidingObjects , glm::vec2* hitDirection, float* minOverlap );
#endif