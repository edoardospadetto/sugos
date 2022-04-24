
Collider2D::Collider2D(std::vector<glm::vec2>&& x_, Polygon shape_): x(x_), shape(shape_)
{

	// Center of Mass, translate. 
	

	
	int N = x.size();
	float invN = 1/float(N);
	/*
	for (int i=0; i<N; i++)
	{
			*xc += x[i].x *invN;
			*yc += x[i].y *invN;
	}
	
	x=x ;
	for (int i=0; i<N; i++)
	{
			x[i].x -= *xc *invN;
			x[i].y -= *yc *invN;
	}
	*/
	// Radius Max.
	
	radius =0;
	float tmp_=0;
	glm::vec2 tmpc{0.0,0.0};
	for (int i=0; i<N; i++)
	{
		tmp_ = glm::length(x[i]-tmpc);
		if (tmp_ >= radius) radius = tmp_;	
	}
	
	//Get Edges normalized
	/*int Nedges = N-1;
	switch(shape)
	{
		
		case SQUARE: 
			Nedges=2
	}*/
	
	// populate normals
	
	for(int i=0; i<N-1; i++)
	{
		glm::vec2 edge_{glm::normalize(x[i+1]-x[i]) };
	 	n.push_back( glm::vec2{edge_.y, -edge_.x}  );
	}
	glm::vec2 edge_{glm::normalize(x[N-1]-x[0])};
	//last normal
	n.push_back( glm::vec2{edge_.y, -edge_.x}  );
	

}


/*
* Check collisions between one colliders and the other. To check correctly use status variable
* and call 2 times symmetrically. Status must be submitted as TO_CHECK and assumes the right value after two calls.
* Min overlap is a float giving the minimum overlap for each normal, and direction is the index of the normal. 
* If Status == TO_CHECK, all these variables are set to a default value. if the min overlap occurs in the second call, 
* Then direction_ is this->normal.size() of the first call + the rigth index for this of the second call.
*
*/


glm::vec2 Collider2D::Check(Collider2D* collider_, CollisionStatus &status_, float& minoverlap_, int& hitdirection_, int& vertex_)
{
	
	glm::vec2 tmpc1{*xc,*yc}, tmpc2{*(collider_->xc),*(collider_->yc)};
	//glm::vec2  rigidReactionDirection{0.0,0.0};
	float a1= 0, b1=0 ;
	float a2=a1, b2= b1;
	float tmp_=0;

	bool overlap=true; 
	int i=0;
	dbglog("                   -- ", status_);
	
	
	// Set variables to get hit direction
	if(status_ == TO_CHECK) 
	{
		minoverlap_=std::numeric_limits<float>::max(); //abs of overlap
		hitdirection_ =0;
	}
	else if (status_ == ON_CHECK) 
	{
		//min overlap stays.
		hitdirection_ = (collider_->n).size();
	}
	
	
	//check if collision
	if(this->PreCheck(collider_ ) ) status_ = NOT_COLLIDING;
	if (status_ !=NOT_COLLIDING)
	{
		for ( auto &normal : this->n)
		{
		
			a1= -std::numeric_limits<float>::max();
			b1= std::numeric_limits<float>::max();
			a2=a1;
			b2=b1;
			i++;
			//find largest projection
			for ( auto vertex : this->x)
			{
				tmp_=glm::dot(tmpc1+vertex, normal);
				if (tmp_>=a1)  a1=tmp_; // higher
				if (tmp_<b1)  b1=tmp_; // lower
				//dbglog( (tmpc1+vertex).x, (tmpc1+vertex).y , "|");
			}
			//dbglog("");
			
			for ( auto vertex : collider_->x)
			{
				tmp_=glm::dot(tmpc2+vertex, normal);
				if (tmp_>=a2)  a2=tmp_;
				if (tmp_<b2)  b2=tmp_;
				//dbglog( (tmpc2+vertex).x, (tmpc2+vertex).y );
			}
			
			bool cnd1= a2>=b1 && a2<a1, cnd2=b2>=b1 && b2<a1, cnd3= a1>=b2 && a1<a2, cnd4= b1>=b2 && b1<a2; 
			bool check =  ( cnd1  or  cnd2  ) or (  cnd3 or cnd4  );
			
			
			
			
			dbglog(i," a1 b1 =", a1, b1, a1-b1, "a2 b2 =", a2, b2, a2-b2, "|", normal.x, normal.y, "|" , status_ );
			
			overlap = overlap && check;
			if (!overlap) 
			{
				status_=NOT_COLLIDING;
				return rigidReactionDirection;
				break;
			}
			if (check) //store for hit direction
			{	
			
				// Minimum overlap cannot occur on a direction
				// Where one collider is inside the other one.
				float tmp_ov = std::numeric_limits<float>::max();
				if ( ( cnd1 && cnd4 )  || ( cnd2 && cnd3 ) )  tmp_ov = std::min( a2-b1, a1-b2); //get the smallest (where the collision occurs), the largest is trivial.
				if ( tmp_ov < 0 )
				{
					printf("Error: Not expected");	
					throw std::exception();
				} 
				
				
				if (tmp_ov < minoverlap_) 
				{
					minoverlap_=tmp_ov
					dbglog("idx", &normal, normal);
					hitdirection = 
					
				}
			}
		}
		dbglog(" ");
		
		//If still on check at the end they must be colliding
		if (overlap && status_==ON_CHECK)
		{
			status_= COLLIDING;
			printf("COLLIDING\n");
			
		}
		else
		{
			status_=ON_CHECK;
		}
		
	}
	
	

	return rigidReactionDirection;
}






bool Collider2D::PreCheck(Collider2D* collider_ )
{
	glm::vec2 tmpc1{*xc,*yc}, tmpc2{ *(collider_->xc),  *(collider_->yc)};
	
	float cdist = glm::distance(tmpc1 , tmpc2);
	return (this->radius + collider_->radius < cdist);
}


void Collider2D::BuildVecObj()
{
	
	
	colliderRep = new VectorizedObject(2,x.size(),x.size(), 2, 2); // Set of Lines
	
	
	for (int i=0; i < x.size(); i++)
	{
		colliderRep->vertex_buffer[2*i]= (x[i].x);
		colliderRep->vertex_buffer[2*i+1]= (x[i].y);
		colliderRep->index_buffer[2*i]= i ;
		colliderRep->index_buffer[2*i+1]= i+1 ;
	}
	colliderRep->index_buffer[2*x.size()-1]=0;
	
	
	colliderRep->SpecifyBuffersAttributes("aPos", 2, GL_LINES);
	colliderRep->LinkUniformToVariable("c", 2);
	
		
	
}

void Collider2D::ResetCenter(float x0, float y0)
{
	
}

