#ifndef PHYSICSOBJECT2D
#define PHYSICSOBJECT2D

#include "./vectorizedobject.h"
#include "../include/safe_include_glm.h"

class  PhysicsObject2D  : virtual public VectorizedObject
{

	protected:
	
		glm::vec2 cumulativeForce          ={0,0};
		glm::vec2 cumulativeImpulse        ={0,0};
		float     cumulativeAngularImpulse =0;
		float     cumulativeAngularForce   =0;  
		
		float omega=0;
		
		glm::vec2 velocity={0,0};
	
	public:
	
		float oneovermass;
		float oneoverI;	
	
	

		PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,GLenum representation_, float mass, float I);
		void ApplyForce(glm::vec2 force_ ); 
		void ApplyImpulse( glm::vec2 impulse_ ); 
		void ApplyAngularImpulse( float angularimpulse_ ); 
		void ApplyAngularForce( float angularforce_ );
		void EulerIntegration(float deltatime_);
		void GetVelocity(float &vx, float &vy);

};

#endif

