#include "./collider.h"

#include <limits>
#include "../modules_/debugmisc_module.h"

#include "../objects_/vectorizedobject.h"


Collider2D::Collider2D(std::vector<glm::vec2>&& x_, Polygon shape_): x(x_), shape(shape_)
{

	// Center of Mass, translate. 
	

	
	int N = x.size();
	if(N < 3)
	{
		printf("ERROR <s:s>: Invalid collider size");// __FILE__, __LINE__ );
	}
	float invN = 1/float(N);

	
	radius =0;
	float tmp_=0;
	glm::vec2 tmpc{0.0,0.0};
	for (int i=0; i<N; i++)
	{
		tmp_ = glm::length(x[i]-tmpc);
		if (tmp_ >= radius) radius = tmp_;	
	}
	
	
	int Nedges = N-1;
	// populate normals and edges
	
	int illnormals =0;
	/*switch (shape)
	{
		case SQUARE :
			illnormals = 2-1;
			break;
	
	}*/
	for(int i=0; i<N-1-illnormals; i++)
	{
		glm::vec2 edge_{glm::normalize(x[i+1]-x[i]) };

	 	n.push_back( glm::vec2{edge_.y, -edge_.x}  );
	}
	if(illnormals==0)
	{
		glm::vec2 edge_{glm::normalize(x[0]-x[N-1])};
			//last normal & edge

		n.push_back( glm::vec2{edge_.y, -edge_.x}  );
	}

	

}


/*
* Check collisions between one colliders and the other. To check correctly use status variable
* and call 2 times symmetrically. Status must be submitted as TO_CHECK and assumes the right value after two calls.
* Min overlap is a float giving the minimum overlap for each normal, and direction is the index of the normal. 
* If Status == TO_CHECK, all these variables are set to a default value. if the min overlap occurs in the second call, 
* Then direction_ is this->normal.size() of the first call + the rigth index for this of the second call.
*
* The this object check its normals, the other object just his vertices. 
*
*/

//Test Version, collision direction not checked yet.

void Collider2D::Check(Collider2D* collider_, CollisionStatus &status_,  glm::vec2* hitDirection_ , float* overlap_,float coeff)
{
	
	//const char* statuses[] =  { "NOT_COLLIDING" , "COLLIDING", "ON_CHECK" , "TO_CHECK"};
	
	glm::vec2 hit_direction{0.0,0.0} ;
	
	glm::vec2 tmpc1{*xc,*yc}, tmpc2{*(collider_->xc),*(collider_->yc)};

	float a1 = 0  , b1 = 0   ;
	float a2 = a1 , b2 = b1  ; 
	
	
	bool lHitDirection= true;
	bool lOverlap=true; 
	
	int ii=-1;
	float _tmp=0;
	float* angle2 = collider_->angle;
	glm::mat2 rotM1 = glm::mat2(cos(*angle),-sin(*angle),
                                    sin(*angle),cos(*angle));	
	glm::mat2 rotM2 = glm::mat2(cos(*angle2),-sin(*angle2),
                 	            sin(*angle2),cos(*angle2));	
	// Set variables to get hit direction
	if (lHitDirection)
	{
		if(status_ == TO_CHECK) 
		{
			* overlap_ = std::numeric_limits<float>::max(); //abs of overlap
			*hitDirection_ =glm::vec2(0.0,0.0);
		}
		
	}
	
	
	//check if collision

	if(this->PreCheck(collider_ ) ) status_ = NOT_COLLIDING;
	if (status_ !=NOT_COLLIDING)
	{
		for ( auto normal : this->n)
		{
			
			a1= -std::numeric_limits<float>::max();
			b1= std::numeric_limits<float>::max();
			a2=a1;
			b2=b1;
			ii++;
			//find largest projection
			for ( auto vertex : this->x) 
			{
				_tmp=glm::dot(tmpc1+rotM1*vertex, rotM1*normal);
				
				if (_tmp>=a1)   a1=_tmp;
				if (_tmp<b1)  	b1=_tmp;
			}
		
			
			for ( auto vertex : collider_->x)
			{
				_tmp=glm::dot(tmpc2+rotM2*vertex, rotM1*normal);
				
				if ( _tmp>=a2) a2=_tmp;
				if ( _tmp<b2 ) b2=_tmp;
			}
			
			//verify intersection conditions
			bool cnd1= a2>=b1 && a2<a1, cnd2=b2>=b1 && b2<a1, cnd3= a1>=b2 && a1<a2, cnd4= b1>=b2 && b1<a2; 
			bool check =  ( cnd1  or  cnd2  ) or (  cnd3 or cnd4  );
			
			
			//Check if not colliding
			lOverlap = lOverlap && check;
			if (!lOverlap) 
			{
				status_=NOT_COLLIDING;
			
				return;
				break;
			}
			//If collision possible store for hit direction
			if (check && lHitDirection) 
			{	
			
				// Minimum overlap cannot occur on a direction
				// Where one collider is inside the other one.
				float _tmpOv = std::numeric_limits<float>::max();
				float direction = 0;
				//Get the smallest (where the collision occurs), the largest is trivial.
				//Get the direction of collision (before collision) of this
				_tmpOv = std::min( a2-b1, a1-b2); 
				
				direction = +1*int(a1-b2 < a2-b1) -1*int(a1-b2 >= a2-b1);
				
				//dbglog(ii," a1 b1 =", a1, b1, a1-b1, "a2 b2 =", a2, b2, a2-b2, "|", normal.x, normal.y, "|" , status_  ,"|",
				//	 cnd1,cnd2,cnd3,cnd4, " | ", direction); 
				
				if (_tmpOv < 0 )
				{
					printf("Error: Not expected a negative overlap");	
					throw std::exception();
				} 
				
				
				if (_tmpOv < *overlap_) 
				{
					*overlap_ = _tmpOv;
					*hitDirection_ = direction*rotM1*normal*coeff;
					
					
				}
			}
			
		}
	
		
		//if (status==ON_CHECK) hitdirection += collider_.size(n); 
		//dbglog("idx", ii, minoverlap_);
		//If still on check at the end they must be colliding
		if (lOverlap && status_==ON_CHECK)
		{
			
			status_= COLLIDING;
			//printf("COLLIDING\n");
			
		}
		else
		{
			status_=ON_CHECK;
		}
		
	}

	
	

}




/*
* Checks if two colliders are closer than the sum of the maxima radii 
* that contains a portion of the collider
*/

bool Collider2D::PreCheck(Collider2D* collider_ )
{
	glm::vec2 tmpc1{*xc,*yc}, tmpc2{ *(collider_->xc),  *(collider_->yc)};
	
	float cdist = glm::distance(tmpc1 , tmpc2);
	return (this->radius + collider_->radius < cdist);
}

/*
* Build the poligon representing 
* the collider
*/
void Collider2D::BuildVecObj()
{
	
	dbglog(x.size());
	colliderRep = new VectorizedObject(2,x.size(),x.size(), 2, GL_LINES); // Set of Lines
	
	
	for (int i=0; i < x.size(); i++)
	{
		colliderRep->vertex_buffer[2*i]   = x[i].x;
		colliderRep->vertex_buffer[2*i+1] = x[i].y;
		colliderRep->index_buffer[2*i]    = i ;
		colliderRep->index_buffer[2*i+1]  = i+1 ;
	}
	
	colliderRep->index_buffer[2*x.size()-1]=0;
	colliderRep->SpecifyBuffersAttributes("aPos", 2);
	colliderRep->LinkUniformToVariable("c", 3);
	
		
}

/*
void Collider2D::(Collider2D&& collider_)
{
	this->x =  std::move( collider_.x ) ;
	this->x =  std::move( collider_.e ) ;
	this->x =  std::move( collider_.n ) ;
	
	
	xc= collider_.xc; 
	yc= collider_.yc; 
	
}
*/


