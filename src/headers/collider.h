
#ifndef COLLIDER2D
#define COLLIDER2D




class VectorizedObject;

class Collider2D
{
	private :
	Polygon shape = GENERIC; 
	bool PreCheck(Collider2D* collider_ );
	int N =0;
	bool lhitPoints = false; 
	//debug 
	void Render();
	
	public : 
	void ResetCenter(float x0, float y0);
	Collider2D(std::vector<glm::vec2>&& x_, Polygon shape_);
	void Check(Collider2D* collider_, CollisionStatus &status_,  glm::vec2* hitDirection_ , float* overlap_, float coeff);
	
	/*
	* x : vertices of collider
	* e : edges of the polygon, starting from the right vertex
	* n : normal corresponding to the edge
	*/
	
	std::vector<glm::vec2> x;
	std::vector<glm::vec2> e;
	std::vector<glm::vec2> n;
	
	float *xc, *yc, *angle;
	float radius=0.0;
	
	
	VectorizedObject* colliderRep;
	void BuildVecObj();
			
};

#endif
