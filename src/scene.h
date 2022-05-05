/*class PhysicsEngine
{
	
	
	glm::vec2* hitDirection;
	PhysicsEngine( size_t bodySetSize );
	void EvolveObj();
	
};*/

class CollisionEngine
{
	public: 
	float* minOverlap;	
	std::vector<int> collidingObjects;
	std::vector<PhysicsObject2D*> collisionSet;
	
	glm::vec2* hitDirection ;
	
	int Ncoll;
	
	
	void UpdateDbgColliders();
	void StartCollisions();
	void HandleCollisions();
	void VerifyCollisions();
	void EndCollisions();
	
	void LoadCollidingObject(PhysicsObject2D* tmpObj_);
};


//=======================================================================================
//=================================   Debug   ===========================================
//=======================================================================================

void CollisionEngine::UpdateDbgColliders()
{
	for (auto obj : collisionSet )
	{
		obj->collider->colliderRep->SetUniform("c",0,*(obj->collider->xc));
		obj->collider->colliderRep->SetUniform("c",1,*(obj->collider->yc));
	}	


}

//=======================================================================================
	

void CollisionEngine::VerifyCollisions()
{

	CollisionStatus coupleStatus;
	//debug
	const char* statuses[] =  { "NOT_COLLIDING" , "COLLIDING", "ON_CHECK" , "TO_CHECK"};
	
	int index = 0;
	
	

	for (int i=1;  i< Ncoll ; i++ )
	{
		//dbglog(i, Ncoll);
		Collider2D *c1 = collisionSet[i]->collider;
	
	for (int j=0;  j< i ;j++ )
	{
	
		coupleStatus=TO_CHECK;
	
		Collider2D *c2 = collisionSet[j]->collider;
		
		index = i*(i-1)/2 +j;
		//dbglog("index ",index);
		/*
		* hit direction positive if c1 colliding towords right.
		* if i<j then 1 else -1, to simmetrize hit direction
		*/ 
		
		c1->Check(c2, coupleStatus, &(hitDirection[index]), &(minOverlap[index]), +1.0 );
		c2->Check(c1, coupleStatus, &(hitDirection[index]), &(minOverlap[index]), -1.0 );
	
		
		
		
		
		if ( coupleStatus == COLLIDING ) collidingObjects.push_back(index);
				
		
	}
	}

}

void CollisionEngine::HandleCollisions()
{

	//TEMP
	
	
	float eps = 0.0001;
	
	
			
	/*
	* colliding objects contains linearized coordinates of a lower triangular matrix without
	* diagonal. To get back the inices of row and column, i.e. the 2 objects we use the following.
	*/
	
	
	for (auto index : collidingObjects)	
	{
		int row =  ceil ((-1 + sqrt(2+8*index) )/2.0 -1 ) +1 ;
	  	int col =  index- ( row*(row-1)/2 )  ;
		
		PhysicsObject2D *obj1 = collisionSet[row ];
		PhysicsObject2D *obj2 = collisionSet[col ];
		
		
		glm::vec2 edge{-hitDirection[index].y, hitDirection[index].x};
		glm::vec2 velocity{obj1->velocity[0],obj1->velocity[1]};
		
		
		if ( glm::length(velocity)  >= float(1e-10))
		{
			glm::vec2 final_move = glm::dot(edge,velocity)*edge;
			glm::vec2 velocity_dir = glm::normalize(velocity);
		
			//obj1->position[0] -=  velocity.x - final_move.x;
			//obj1->position[1] -=  velocity.y - final_move.y;
			//obj1->lastPosition[0] = obj1->position[0] ;
			//obj1->lastPosition[1] -= obj1->position[1] ;
			//obj1->velocity[0] = final_move.x;
			//obj1->velocity[1] = final_move.y;
			minOverlap[index]+=eps;
			obj1->position[0] -= minOverlap[index]*hitDirection[index].x;// -  final_move.x;
			obj1->position[1] -= minOverlap[index]*hitDirection[index].y;// -  final_move.y;
			
			
			//dbglog("dir ;", hitDirection[index].x, hitDirection[index].y, "ov " ,  velocity_dir.x,  velocity_dir.y );
		}
		
	}


}


void CollisionEngine::LoadCollidingObject(PhysicsObject2D* tmpObj_)
{
	if(tmpObj_ != nullptr) // Go on with animation temp_obj->Animate();
	{	
		
		if (&(tmpObj_->collider) == nullptr)
		{
			printf("ERROR, collider is not defined\n ");
			throw std::exception();
		} 
		else this->collisionSet.push_back(tmpObj_);
		
	}
	

}

void CollisionEngine::StartCollisions()
{
	Ncoll = collisionSet.size();
	minOverlap = new float[ ((Ncoll)*(Ncoll-1))/2 ];
	hitDirection = new glm::vec2[ ((Ncoll)*(Ncoll-1))/2 ];
}


void CollisionEngine::EndCollisions()
{
	collidingObjects.clear();
	delete [] hitDirection ;
	delete [] minOverlap;
}






/*
* A scene is everything that is on screen now and on the near future.
* It hangles all the call to OpenGL given the objects it has to draw.
*/




class Scene
{
	private: 
		
		bool ldbgcolliders = false;
		CollisionEngine sceneCollisionEngine;
		
		GLuint VBO = 0;
		GLuint IBO = 0;
		uint vertexbuffersize=0, indexbuffersize=0;
		std::vector<std::vector<VectorizedObject*>> assets;
		std::vector<GLuint> programs;
		
		
		
		GLuint collidersdbg_pragma;
		GPUcodes collidersdebug = GPUcodes("./data/debugutils/colliders_debug.gls");
	
	public:
	
		Scene();		 
		void Render();
		void LoadObj(VectorizedObject& obj, GLuint designatedprogram);
		void Prepare();
		void ProgramUniforms(VectorizedObject* obj);
		void UnloadObject(VectorizedObject& obj);
		void Collisions();
		void DebugColliders();
		void Update();
		void Animations();
		void Physics();
};


/*
* Dummy constructor, it performs just a call to OpenGL
*/

Scene::Scene()
{
	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &IBO );
}



/*
* PURPOSE
*
* Load an object into the scene and specify which program (OpenGL meaning) to use
* when drawing
*
* DESCRIPTION
*
* The function verify if it has already processed the program before
* if yes it queues the object with all the others assigned to the program
* otherwise it start a new queue for the requested program
*
* Then it checks into the uniforms declared for the object if they are found
* in the program.
*
* Info on the lenght of the buffers are obtained from the object
*
* Checks are performed on the names and location of the attributes of the object
*/




void Scene::LoadObj(VectorizedObject& obj, GLuint designatedprogram)
{

// ================================================================
//		            LOAD GRAPHICS
// ================================================================

	bool lfound = false;
	
	dbglog("designated program=  ", designatedprogram );
	
	for(int i=0; i<programs.size();i++)
	{
		if(programs[i] == designatedprogram)
		{
			assets[i].push_back(&obj);
			dbglog("	the requested program : ", programs[i], " has a queue, adding object");
			lfound = true;
			obj.sceneprog = i ;
			obj.sceneprogidx = assets[i].size()-1; 
			break;
		}
	}
	
	if(!lfound)
	{
		programs.push_back(designatedprogram);
		std::vector<VectorizedObject*> tmp{&obj};
		assets.push_back(tmp);
		obj.sceneprog = assets.size()-1 ;
		obj.sceneprogidx = 0; 
		dbglog("	the requested program : ", designatedprogram, " has no queue, creating one");
	}
	
	for(int i=0; i<obj.uniformnames.size(); i++)
	{
		GLint tmp = glGetUniformLocation(designatedprogram, obj.uniformnames[i].c_str());
		GLenum error = glGetError();
		if(error!=GL_NO_ERROR | tmp==-1) printf("ERROR: uniform %s \n", gl_error_string(error));
		obj.uniformlocationsprogram[i] = tmp;
		dbglog("	link uniform : ", obj.uniformnames[i], "at location " , tmp) ;
	}
	
	uint tmpvbo, tmpibo, vtlen;
	obj.GetBuffersInfo(tmpvbo, tmpibo, vtlen);
	
	vertexbuffersize += tmpvbo*vtlen;
	indexbuffersize +=tmpibo;
	
	for (int i =0; i<obj.attributenames.size(); i++)
	{
		obj.attributelocationsprogram[i] = glGetAttribLocation( designatedprogram, obj.attributenames[i].c_str() );	
		GLenum error = glGetError();
		if(error!=GL_NO_ERROR | obj.attributelocationsprogram[i] == -1) printf("ERROR: attribute %s \n", gl_error_string(error));
		dbglog("	linkbuffer attribute = ",obj.attributenames[i].c_str(), "location =", obj.attributelocationsprogram[i])   ;
		
	}
	
	GLenum error = glGetError();
	if(error!=GL_NO_ERROR) 
	{
		printf("ERROR: Load Object: \n", gl_error_string(error));
		throw std::exception();
	}
	
	
// ================================================================
//		            LOAD COLLISIONS
// ================================================================

	sceneCollisionEngine.LoadCollidingObject(dynamic_cast<PhysicsObject2D*>(&obj)); 
			

	
	
	
}



/*
* PURPOSE
*
* Render all the object stored in the scene
*
* DESCRIPTION
* 
* Render each asset in the scene according to asset render method
* using the right program
*/


void Scene::Collisions()
{
	sceneCollisionEngine.StartCollisions();
	sceneCollisionEngine.VerifyCollisions();
	sceneCollisionEngine.HandleCollisions();
	sceneCollisionEngine.EndCollisions();
	
	if(ldbgcolliders) sceneCollisionEngine.UpdateDbgColliders();	
}



void Scene::Render()
{
	
		
		GLenum error = glGetError();
		GLuint offsetibo=0 , offsetvbo=0, tmpvbo=0, tmpibo=0, vertxlen=0;
		
		for(int i=0; i< assets.size(); i++)
		{
			
			glUseProgram( programs[i] );
			glBindBuffer( GL_ARRAY_BUFFER, VBO );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
			
			//Enable vertex position
			for (int j =0; j< assets[i].size(); j++)
			{
			
				assets[i][j]->Render(VBO,IBO,offsetvbo,offsetibo);
			
			}
				
		}
		error = glGetError();
		if(error!=GL_NO_ERROR) 
		{
			printf("ERROR: Scene::Render ");
			printf("%s \n" , gl_error_string(error));
			throw std::exception();
		}
		
		
		//DEBUG COLLIDERS
		
		
}
/*
* PURPOSE
*
* Handles collisions among physical objects
* 
* DESCRIPTION
* 
* 
*
*/


/*
* PURPOSE
*
* After Loading object in the scene all buffers to gpu have to be loaded
* 
* DESCRIPTION
* 
* Render each asset in the scene according to asset render method
* This is done ordering assets in the gpu buffers by program and then by appearence
*
*/
void Scene::Update()
{
	//Update Animation System
	this->Animations();
	this->Physics();
	this->Collisions();
	
	

	//Render
	this->Render();
}


void Scene::Physics()
{
	for (auto & objset : assets )
	{
		for (auto & obj : objset )
		{
			obj->velocity[0] = obj->position[0]- obj->lastPosition[0];
			obj->velocity[1] = obj->position[1]- obj->lastPosition[1];
			obj->lastPosition[0] = obj->position[0];
			obj->lastPosition[1] = obj->position[1];
		}
	}
	
}



void Scene::Animations()
{
	
	for (auto & objset : assets )
	{
		for (auto & obj : objset )
		{
			AnimatedObject2D* temp_obj{ dynamic_cast<AnimatedObject2D*>(obj) }; 
			
			if(temp_obj != nullptr) // Go on with animation temp_obj->Animate();
			{
				//Triggers not processed by SDL.
				//wenttimeout : If the state just ended and restarted. 
				bool wentTimeOut=false; 
				temp_obj->selfStateEngine->AnimateState(wentTimeOut); // 1st 
				temp_obj->selfStateEngine->ChangeState(wentTimeOut);  // 2nd
				temp_obj->selfStateEngine->UpdateVBatFrame(temp_obj); // 3rd
			}
		} 
	} 
}

void Scene::Prepare()
{
	
	//dbglog("SUMMARY");
	GLenum error = glGetError();
	


	
	for(int i=0; i< assets.size(); i++)
	{
		//dbglog("program", programs[i], "#assets", assets[i].size());
	}
	
	
	//Create VBO
	
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, vertexbuffersize*sizeof(GLfloat), NULL , GL_DYNAMIC_DRAW );
	
	//Create IBO
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indexbuffersize*sizeof(GLuint), NULL  , GL_DYNAMIC_DRAW );
	
	if(error!=GL_NO_ERROR) 
	{
		printf("ERROR: Scene Prepare, Buffers Creation | %s | v.b.size %d |i.b.size %d |\n", gl_error_string(error), vertexbuffersize, indexbuffersize);
		throw std::exception();
	}
	//dbglog("");
	//dbglog(" Indexbuffersize (NUM_SURF*VERT_X_SURF) =", indexbuffersize);
	//dbglog(" Vertexbuffersize (VERT_COUNT*VERT_SIZE) =", vertexbuffersize);
	//dbglog("");

	uint tmpvbo=0, tmpibo=0, vertxlen=0;
	uint offsetvbo=0, offsetibo=0, offsetvbover=0;

	for(int i=0; i< assets.size(); i++)
	{
	for(int j=0; j< assets[i].size(); j++)
	{
		assets[i][j]->GetBuffersInfo(tmpvbo, tmpibo, vertxlen);	
		//dbglog("Sizes: VBO =" ,tmpvbo, "| IBO  = ",tmpibo, "| VLEN  = ", vertxlen);
		glBufferSubData( GL_ARRAY_BUFFER, offsetvbo*sizeof(GLfloat), tmpvbo*vertxlen*sizeof(GLfloat), assets[i][j]->vertex_buffer );
		
		error = glGetError();
		
		if(error!=GL_NO_ERROR) 
		{
			printf("ERROR: Scene Prepare, Vertex Buffer Filling %s asset program %d  index %d\n", gl_error_string(error), i, j);
			throw std::exception();
		}
		
		//for(auto x = assets[i][j]->index_buffer; x != &assets[i][j]->index_buffer[assets[i][j]->surfaces_num*assets[i][j]->vertexxsurf]; ++x) {*x+=offsetvbover;}
		glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, offsetibo*sizeof(GLuint), tmpibo*sizeof(GLuint), assets[i][j]->index_buffer );
		//for(auto x = assets[i][j]->index_buffer; x != &assets[i][j]->index_buffer[assets[i][j]->surfaces_num*assets[i][j]->vertexxsurf]; ++x) {*x-=offsetvbover;}
		
		offsetvbo+=tmpvbo*vertxlen;
		offsetibo+=tmpibo;
		offsetvbover+=tmpvbo;
	
		error = glGetError();
		
		if(error!=GL_NO_ERROR) 
		{
			printf("ERROR: Scene::Prepare-IBO filling: %s | AssetsProgram %d | AssetsProgramIndex %d\n", gl_error_string(error), i, j);
			throw std::exception();
		}
	}
	}
	

	//dbglog("Buffers Filled ");
	
	
	
}



void Scene::UnloadObject(VectorizedObject& obj)
{	
	dbglog("test A1", assets[obj.sceneprog].size());
	assets[obj.sceneprog].erase(assets[obj.sceneprog].begin()+obj.sceneprogidx);
	dbglog("test A2", assets[obj.sceneprog].size());
	uint tmpvbo, tmpibo, vtlen;
	obj.GetBuffersInfo(tmpvbo, tmpibo, vtlen);
	vertexbuffersize -= tmpvbo*vtlen;
	indexbuffersize -=tmpibo;
	if(assets[obj.sceneprog].size() == 0)
	{
		assets.erase(assets.begin()+obj.sceneprog);
		dbglog("test9");
		for (int i =obj.sceneprog; i < assets.size(); i++ )
		{
			for (int j =0; j < assets[i].size(); j++ )
			{
				assets[i][j]->sceneprog = i ;
			}
		}
	}
	for (int j =obj.sceneprogidx; j < assets[obj.sceneprog].size(); j++ )
	{
		assets[obj.sceneprog][j]->sceneprogidx = j ;
	}

	for(int i=0; i<assets.size(); i++)
	{

		for (int j =0; j < assets[i].size(); j++ )
	{
	
	}


	}
		
	//TEMP
	Prepare();
	
	//TO DO! 
	/*Get position of the removed object* =LOC 
	**Copy buffer[0:LOC] to newbuffer[0:LOC]
	**Copy buffer[LOC+SIZE: buffersize] to newbuffer[LOC+1: buffersize-SIZE]
	**Use the new buffer instead of the old one, both IBO and VBO*/

}

void Scene::DebugColliders()
{

	collidersdebug.Load("debug_colliders_vertex","debug_colliders_fragment", "debug_colliders");
	
	for (auto obj : sceneCollisionEngine.collisionSet )
	{
		obj->collider->BuildVecObj();
		this->LoadObj( *(obj->collider->colliderRep), collidersdebug.glprograms[0]);
	}
	ldbgcolliders=true;
}


// TO DO
//void Scene::Renovate()
/* PURPOSE
* if parts of the CPU buffers are modified
* this function through a system to keep track of it
* should buffersubdata only the modified parts
* and not create a new buffer.
*
*/
