#include "./vectorizedobject.h"
class  PhysicsObject2D  : virtual public VectorizedObject
{
	public:
	
	float* velocity;
	float omega;
	float oneovermass;
	float oneoverI;
	PhysicsObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,GLenum representation_, float mass, float I);
	std::map<std::string, float> momenta;
	std::map<std::string, glm::vec2> forces;
	
	glm::vec2 cumulativeForce;
	float cumulativeMomenta;
	
	void AddForce(const std::string &name, glm::vec2 force );
	void AddMomenta(const std::string &name, float val );
	void ComputeActions();
	void TemporalEvolution(float deltatime_);
	
	
	
	void Dynamics();
};



