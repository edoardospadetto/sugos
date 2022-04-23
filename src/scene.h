/*
* A scene is everything that is on screen now and on the near future.
* It hangles all the call to OpenGL given the objects it has to draw.
*/


class Scene
{
	private: 
	
		GLuint VBO = 0;
		GLuint IBO = 0;
		uint vertexbuffersize=0, indexbuffersize=0;
		std::vector<std::vector<VectorizedObject*>> assets;
		std::vector<GLuint> programs;
		std::vector<PhysicsObject2D*> collisionSet;
		
		bool ldbgcolliders = false;
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
	
	
	//Enable physics
	PhysicsObject2D* temp_obj{ dynamic_cast<PhysicsObject2D*>(&obj) }; 
			
	if(temp_obj != nullptr) // Go on with animation temp_obj->Animate();
	{	
		
		if (&(temp_obj->collider) == nullptr)
		{
			printf("ERROR, collider is not defined\n ");
			throw std::exception();
		} 
		
		collisionSet.push_back(temp_obj);	
	}
	
	
	
	
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
			printf("ERROR: Scene::Render \n");
			throw std::exception();
		}
		
		
		//DEBUG COLLIDERS
		
		
}


void Scene::Collisions()
{
	
	CollisionStatus *coupleStatus;
	int Ncoll = collisionSet.size()-1;
	int index = 0;
	coupleStatus = new CollisionStatus[ ((Ncoll)*(Ncoll+1))/2 ];
	for (int i=0; i<((Ncoll)*(Ncoll+1))/2; ++i)
	{
		coupleStatus[i] = TO_CHECK;
	}   
	for (int i=0;  i< Ncoll+1 ; i++ )
	{
		PhysicsObject2D *obj1 = collisionSet[i];
		for (int j=0;  j< Ncoll+1;j++ )
		{
			if(i!=j)
			{
				index = std::min(i,j)*(Ncoll-1)+std::max(i,j)-1;
				PhysicsObject2D *obj2 = collisionSet[j];
				dbglog("                                          ", coupleStatus[index], TO_CHECK, index, i , j ) ;
				obj1->collider->Check(obj2->collider, coupleStatus[index] );
			}
		} 
	} 
	dbglog("-----------");
	delete[] coupleStatus;
	
}

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
	this->Collisions();
	
	//=======================================================================================
	//=================================   Debug   ===========================================
	//=======================================================================================
	
	if(ldbgcolliders)
	{
		for (auto obj : collisionSet )
		{
			obj->collider->colliderRep->SetUniform("c",0,*(obj->collider->xc));
			obj->collider->colliderRep->SetUniform("c",1,*(obj->collider->yc));
		}	
	}
	//=======================================================================================
	
	//Render
	this->Render();
}


// Safe? Unsafe? No idea...
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
	printf("%d  -- ", i);
		for (int j =0; j < assets[i].size(); j++ )
	{
		printf(" %d ", j);
	}
	printf("\n");

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
	
	for (auto obj : collisionSet )
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
