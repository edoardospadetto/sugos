enum Polygon {GENERIC =0, SQUARE = 1};
enum CollisionStatus { NOT_COLLIDING = 0 , COLLIDING = 1, ON_CHECK=2 , TO_CHECK=3};


class VectorizedObject;

class Collider2D
{
	private :
	Polygon shape = GENERIC; 
	bool PreCheck(Collider2D* collider_ );
	int N =0;
	
	//debug 
	void Render();
	
	public : 
	void ResetCenter(float x0, float y0);
	Collider2D(std::vector<glm::vec2>&& x_, Polygon shape_);
	glm::vec2 Check(Collider2D* collider_, CollisionStatus &status_ );
	std::vector<glm::vec2> x;

	std::vector<glm::vec2> n;
	float *xc, *yc;
	float radius=0.0;
	
	
	VectorizedObject* colliderRep;
	void BuildVecObj();
			
};


