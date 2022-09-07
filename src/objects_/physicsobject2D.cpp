#include "./physicsobject2D.h"
PhysicsObject2D::PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_, GLenum representation_, float mass, float I ) //:
//VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, 2, representation_)
{
	this->Fill( vertex_len_, vertex_num_, surfaces_num_, 2, representation_);
	this->Init();
	oneovermass = 1.0/mass;	
	oneoverI = 1.0/ I ; 
}

void PhysicsObject2D::ApplyForce(glm::vec2 force_ ) {cumulativeForce+=force_;}

void PhysicsObject2D::ApplyImpulse( glm::vec2 impulse_ ) {cumulativeImpulse+=impulse_;}

void PhysicsObject2D::ApplyAngularImpulse( float angularimpulse_ ) {cumulativeAngularImpulse+=angularimpulse_;}

void PhysicsObject2D::ApplyAngularForce( float angularforce_ ) {cumulativeAngularForce+=angularforce_;}


void PhysicsObject2D::EulerIntegration(float deltatime_)
{
	float deltavx =  ( cumulativeForce.x  * deltatime_   + cumulativeImpulse.x    ) *oneovermass;
	float deltavy =  ( cumulativeForce.y  * deltatime_   + cumulativeImpulse.y    ) *oneovermass;
	float deltaw  =  ( cumulativeAngularForce * deltatime_ + cumulativeAngularImpulse ) *oneoverI ;
	
	
	this->position[0] += ( this->velocity[0] +  0.5*deltavx ) *deltatime_;
	this->position[1] += ( this->velocity[1] +  0.5*deltavy ) *deltatime_;
	this->velocity.x  += deltavx ;
	this->velocity.y  += deltavy ;
	this->angle       += ( this->omega + 0.5*deltaw ) *deltatime_;
	this->omega       += deltaw;

	cumulativeForce          = {0,0};
	cumulativeImpulse        = {0,0};
	cumulativeAngularForce   = 0; 
	cumulativeAngularImpulse = 0;
}


void PhysicsObject2D::GetVelocity(float &vx, float &vy)
{
    vx = this->velocity.x;
    vy = this->velocity.y;
}   
