#ifndef COLLISIONHANDLING
#define COLLISIONHANDLING
#include <vector>
#include "../include/glm.h"

class ColliderObject2D;
void RigidCollision(std::vector<ColliderObject2D*> &collisionSet , std::vector<int> &collidingObjects , glm::vec2* hitDirection, float* minOverlap );
#endif
