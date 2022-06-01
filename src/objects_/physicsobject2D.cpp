/*
PhysicsObject2D::PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_, GLenum representation_, float mass, float I ) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, 2, representation_)
{
	velocity = new float[2];
	oneovermass = 1.0/mass;	
	oneoverI = 1.0/ I ; 
}

void PhysicsObject2D::AddForce(const std::string &name, glm::vec2 force_ )
{
	forces[name] = force_;
}

void PhysicsObject2D::AddMomenta(const std::string &name, float momentum_ )
{
	momenta[name] = momentum_;
}
/*
void PhysicsObject2D::AddImpulse(float px, float py)
{
	
}
*/
/*
void PhysicsObject2D::ComputeActions()
{

	cumulativeForce = glm::vec2(0.0,0.0);
	cumulativeMomenta = 0.0;
	for(auto f=forces.begin(); f!=forces.end(); ++f)
	{
      		cumulativeForce +=  (f->second) ;
   	}
   	for(auto m=momenta.begin(); m!=momenta.end(); ++m)
	{
      		cumulativeMomenta +=  (m->second) ;
   	}
   	
}

void PhysicsObject2D::TemporalEvolution(float deltatime_)
{
	float deltavx =  cumulativeForce.x * oneovermass * deltatime_;
	float deltavy =  cumulativeForce.y * oneovermass * deltatime_;
	float deltaw  =  cumulativeMomenta * oneoverI * deltatime_;
	
	
	this->position[0] += this->velocity[0]*deltatime_ +  0.5*deltavx*deltatime_;
	this->position[1] += this->velocity[1]*deltatime_ +  0.5*deltavy*deltatime_;
	this->velocity[0] += deltavx ;
	this->velocity[1] += deltavy ;
	this->angle       += this->omega*deltatime_ +  0.5*deltaw*deltatime_;
	this->omega       += deltaw;

}
*/
