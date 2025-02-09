#include "./scene.h"

#include <exception>
#include <algorithm>

#include "../include/safe_include_SDLGL_OpenGL.h"
#include "../modules_/debugmisc_module.h"
#include "../engines_/stateengine.h"
#include "../engines_/collisionengine.h"
#include "../context_/gpucodes.h"
#include "../objects_/instancedobject.h"
#include "../objects_/animatedobject2D.h"
#include "../attributes_/collider.h"
#include "../attributes_/state.h"
#include "../modules_/debugmisc_module.h"

void Scene::SetCollisionHandler(void (*CollisionHandler_)( std::vector<ColliderObject2D*>&, std::vector<int>& , glm::vec2*, float* ) )
{
	sceneCollisionEngine.SetCollisionHandler(CollisionHandler_);
}

/*
* Dummy constructor, it performs just a call to OpenGL
*/

Scene::Scene()
{


	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &IBO );
	glGenBuffers( 1, &TBO );
}

// kind GL_ACTIVE_ATTRIBUTES or GL_ACTIVE_UNIFORMS
std::vector<std::string> Scene::GetVarNamesFromShader(GLuint designatedprogram, GLenum kind)
{

	std::vector<std::string> varNames;

	const GLsizei bufSize = 16; // maximum name length
	GLsizei length; // name length
	GLint count;
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)



	GLchar name_temp[bufSize];


	glGetProgramiv(designatedprogram, kind, &count);
	//printf("Active Attributes: %d\n", count);

	for (int i = 0; i < count; i++)
	{

	    if (kind == GL_ACTIVE_ATTRIBUTES) glGetActiveAttrib(designatedprogram, (GLuint)i, bufSize, &length, &size, &type, name_temp);
	    else if (kind == GL_ACTIVE_UNIFORMS) glGetActiveUniform(designatedprogram, (GLuint)i, bufSize, &length, &size, &type, name_temp);

	    // Ignore Samplers for now just this one
	   if(type != GL_SAMPLER_2D )
	   {

	    	varNames.push_back(name_temp);
	   // 	std::cout << name_temp << "\n";
	   }
	   else
	   {
	         std::cout << "Temporary warning to be fixed" << std::endl;
	         std::cout << "SAMPLERS 2D are ignored, they should be activated from the Texture interface" << std::endl;
	         std::cout << "Also other textures should be handled this way." << std::endl;

	   }
	}

	return varNames;

}


void Scene::LoadShaderVars(std::vector<std::string>& objAtrbNames,std::vector<int>& objAtrbLocs,
			    GLuint designatedprogram, std::vector<std::string>& atrbNames, GLint kind )
{
	std::string nameKind = "";
	if (kind == GL_ACTIVE_ATTRIBUTES) nameKind = "attribute";
	else if (kind == GL_ACTIVE_UNIFORMS) nameKind = "uniform";

	GLsizei bufSize_;
	GLsizei length_;
	GLint size_;
	GLenum type_;
    GLchar* name_ = new GLchar[128];


	for (int i =0; i<objAtrbNames.size(); i++)
	{
		auto temp_it = std::find(atrbNames.begin(), atrbNames.end(), objAtrbNames[i]);
		if (  temp_it != atrbNames.end())
		{
			if (kind == GL_ACTIVE_ATTRIBUTES)
			{
			    objAtrbLocs[i] = glGetAttribLocation(designatedprogram , objAtrbNames[i].c_str() );
			    //glGetActiveAttrib(	designatedprogram,objAtrbLocs[i], 128, &length_, &size_,&type_,name_);
			}
			else if (kind == GL_ACTIVE_UNIFORMS)
			{
			    objAtrbLocs[i] =  glGetUniformLocation(designatedprogram, objAtrbNames[i].c_str());
			    //glGetActiveUniform(	designatedprogram,objAtrbLocs[i], 128, &length_, &size_,&type_,name_);
			}

			//dbglog("|",size_, length_,type_,name_,"|");
			GLenum error = glGetError();

			if(error!=GL_NO_ERROR | objAtrbLocs[i] == -1)
			{
				printf("%s %d OpenGL Error: %s for %s %s\n",__FILE__, __LINE__, gl_error_string(error),nameKind.c_str(), atrbNames[i].c_str());
				throw std::exception();
			}

			dbglog("	linkbuffer ",nameKind," = ",objAtrbNames[i].c_str(), "location =", objAtrbLocs[i]);

			atrbNames.erase(temp_it);
		}
		else
		{
			printf("Error, attribute %s not found in shader program\n", objAtrbNames[i].c_str());
			throw std::exception();
		}
	}

	delete[] name_;

}

void Scene::CheckAnyForgottenVar(std::vector<std::string>& varNames )
{
	if( varNames.size()>0)
	{
		printf("Error, var for shader not binded to CPU side:\n");
		for(int i=0; i< (int) (varNames.size()); i++)
		{
			printf("	%s\n",  varNames[i].c_str());
		}
		throw std::exception();
	}

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




void Scene::LoadObject(VectorizedObject* obj, GLuint designatedprogram)
{

// ================================================================
//		            LOAD GRAPHICS
// ================================================================

	bool lfound = false;

	dbglog("designated program=  ", designatedprogram );

	for(uint i=0; i<programs.size();i++)
	{
		if(programs[i] == designatedprogram)
		{
			assets[i].push_back(obj);
			dbglog("	the requested program : ", programs[i], " has a queue, adding object");
			lfound = true;
			obj->sceneprog = i ;
			obj->sceneprogidx = assets[i].size()-1;
			break;
		}
	}
	if(!lfound)
	{
		programs.push_back(designatedprogram);
		std::vector<VectorizedObject*> tmp{obj};
		assets.push_back(tmp);
		obj->sceneprog = assets.size()-1 ;
		obj->sceneprogidx = 0; //ever used?
		dbglog("	the requested program : ", designatedprogram, " has no queue, creating one");
	}

	glCheckError();

	//load uniforms
	std::vector<std::string> unifNames = this->GetVarNamesFromShader(designatedprogram,GL_ACTIVE_UNIFORMS);
	this->LoadShaderVars(obj->uniformnames,obj->uniformlocationsprogram, designatedprogram, unifNames,GL_ACTIVE_UNIFORMS);
	this->CheckAnyForgottenVar( unifNames );

    glCheckError();

	//load attributes
	uint tmpvbo, tmpibo, vtlen;
	obj->GetBuffersInfo(tmpvbo, tmpibo, vtlen);
	vertexbuffersize += tmpvbo*vtlen;
	indexbuffersize +=tmpibo;
	std::vector<std::string> atrbNames = this->GetVarNamesFromShader(designatedprogram,GL_ACTIVE_ATTRIBUTES);
	this->LoadShaderVars(obj->attributenames,obj->attributelocationsprogram, designatedprogram, atrbNames,GL_ACTIVE_ATTRIBUTES);

	//load attributes of instanced obj
	InstancedObject *tmpInstanced = dynamic_cast<InstancedObject*>(obj);
	if(tmpInstanced!=nullptr)
	{
		uint tmptbo, instancesize;
		//removed a loop over instanced names should be unnecessary
		//a test with 2 instanced buffers will reveal.
		tmpInstanced->InstancedBufferInfo(tmptbo, instancesize );
		this->instanceBufferSize += tmptbo*instancesize;
		this->LoadShaderVars(tmpInstanced->instanceattributenames,
				      tmpInstanced->instanceattributelocationsprogram,
				      designatedprogram, atrbNames,GL_ACTIVE_ATTRIBUTES);

	}
	this->CheckAnyForgottenVar( atrbNames );

	glCheckError();


// ================================================================
//		            LOAD COLLISIONS
// ================================================================

	sceneCollisionEngine.LoadCollidingObject(dynamic_cast<ColliderObject2D*>(obj));
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
		GLuint offsetibo=0 , offsetvbo=0, offsettbo=0;

		for(int i=0; i< assets.size(); i++)
		{

			glUseProgram( programs[i] );
			glCheckError();
			glBindBuffer( GL_ARRAY_BUFFER, VBO );
			glCheckError();
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
			glCheckError();
			//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, TBO );
			glCheckError();
			//Enable vertex position
			for (int j =0; j< (int)(assets[i].size()); j++)
			{

				InstancedObject* tmpInstanced=dynamic_cast<InstancedObject*>(assets[i][j]);
				if( tmpInstanced != nullptr)
				{
					tmpInstanced->Render(VBO,IBO,TBO,offsetvbo,offsetibo,offsettbo);
				}
				else
				{
					 assets[i][j]->Render(VBO,IBO,offsetvbo,offsetibo);
				}


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


	//this->ReBuffer();
	//Render
	this->Render();
}


void Scene::Physics()
{
	/*
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
	*/
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
				bool tmpar=false;
				if( temp_obj->selfStateEngine->CheckFrameUpdate() )
				{
					tmpar = temp_obj->selfStateEngine->NextFrame();
				}
				temp_obj->selfStateEngine->ChangeState(tmpar);  // 2nd
				temp_obj->SetAnimationRestarted(tmpar);
				temp_obj->selfStateEngine->UpdateVBatFrame(temp_obj); // 3rd
			}
		}
	}
}

void Scene::Prepare()
{

	//dbglog("SUMMARY");
	GLenum error = glGetError();




	for(int i=0; i< (int) (assets.size()); i++)
	{
		//dbglog("program", programs[i], "#assets", assets[i].size());
	}


	//Create VBO

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, vertexbuffersize*sizeof(GLfloat), NULL , GL_DYNAMIC_DRAW );

	//Create IBO
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, indexbuffersize*sizeof(GLuint), NULL  , GL_DYNAMIC_DRAW );

	//Create TBO
	glBindBuffer( GL_ARRAY_BUFFER, TBO );
	glBufferData( GL_ARRAY_BUFFER, this->instanceBufferSize*sizeof(GLfloat), NULL , GL_DYNAMIC_DRAW );

	error = glGetError();
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
	uint offsettbo=0, tmptbo=0, tbolen=0;

	for(int i=0; i< (int)(assets.size()); i++)
	{
	for(int j=0; j< (int)(assets[i].size()); j++)
	{
		assets[i][j]->GetBuffersInfo(tmpvbo, tmpibo, vertxlen);

		this->BufferVBO(assets[i][j],tmpvbo, vertxlen, offsetvbo,  offsetvbover);

		offsetvbo+=tmpvbo*vertxlen;
		offsetvbover+=tmpvbo;

		this->BufferIBO(assets[i][j], tmpibo, offsetibo);

		offsetibo+=tmpibo;

		InstancedObject* instancedTmp = dynamic_cast<InstancedObject*>(assets[i][j]);
		if(instancedTmp != nullptr)
		{
			instancedTmp->InstancedBufferInfo(tmptbo, tbolen);
			this->BufferTBO( instancedTmp, tmptbo, tbolen, offsettbo);
			//offsettbo+=tmptbo*tbolen;
			// ?? Never Texted, this comment can be removed when two particle system are present at once

		}




	}
	}




}



void Scene::UnloadObject(VectorizedObject& obj)
{
	if (  assets[obj.sceneprog][obj.sceneprogidx] != &obj )
	{
	    printf("Error %s:%d %s: The object queried is not loaded in the scene", __FILE__ , __LINE__ , __FUNCTION__);
	    return;
	}

	assets[obj.sceneprog].erase(assets[obj.sceneprog].begin()+obj.sceneprogidx);

	uint tmpvbo, tmpibo, vtlen;
	obj.GetBuffersInfo(tmpvbo, tmpibo, vtlen);
	vertexbuffersize -= tmpvbo*vtlen;
	indexbuffersize -=tmpibo;
	if(assets[obj.sceneprog].size() == 0)
	{
		programs.erase(programs.begin()+obj.sceneprog);
		assets.erase(assets.begin()+obj.sceneprog);
		for (int i =obj.sceneprog; i < (int)(assets.size()); i++ )
		{
			for (int j =0; j < assets[i].size(); j++ )
			{
				assets[i][j]->sceneprog = i ;
			}
		}
	}
	for (int j =obj.sceneprogidx; j < (int) (assets[obj.sceneprog].size()); j++ )
	{
		assets[obj.sceneprog][j]->sceneprogidx = j ;
	}


	ColliderObject2D *tmpCollider = dynamic_cast<ColliderObject2D*>(&obj);
	if(tmpCollider != nullptr) sceneCollisionEngine.UnloadObject(tmpCollider);




	//TEMP
	Prepare();

	//TO DO!
	/*Get position of the removed object* =LOC
	**Copy buffer[0:LOC] to newbuffer[0:LOC]
	**Copy buffer[LOC+SIZE: buffersize] to newbuffer[LOC+1: buffersize-SIZE]
	**Use the new buffer instead of the old one, both IBO and VBO*/

}

void Scene::DebugColliders(Window_Class* parent)
{
	collidersdebug = new GPUcodes(parent ,"./src/shaders_/collidersdebug.shader");
	collidersdebug->Load("debug_colliders_vertex","debug_colliders_fragment", "debug_colliders");

	for (auto obj : sceneCollisionEngine.collisionSet )
	{
		obj->collider->BuildVecObj();
		this->LoadObject( obj->collider->colliderRep, collidersdebug->glprograms[0]);
	}
	ldbgcolliders=true;
}


void Scene::ReBuffer()
{

	uint tmpvbo=0, tmpibo=0, vertxlen=0;
	uint offsetvbo=0, offsetibo=0, offsetvbover=0;
	uint offsettbo=0, tmptbo=0, tbolen=0;

	for(int i=0; i< (int) (assets.size()); i++)
	{
	for(int j=0; j< (int) (assets[i].size()); j++)
	{

		assets[i][j]->GetBuffersInfo(tmpvbo, tmpibo, vertxlen);
		if(assets[i][j]->lmodvb) this->BufferVBO(assets[i][j],tmpvbo, vertxlen, offsetvbo,  offsetvbover);
		offsetvbo+=tmpvbo*vertxlen;
		offsetvbover+=tmpvbo;
		if(assets[i][j]->lmodib) this->BufferIBO(assets[i][j], tmpibo, offsetibo);

		offsetibo+=tmpibo;

		InstancedObject* instancedTmp = dynamic_cast<InstancedObject*>(assets[i][j]);
		if(instancedTmp != nullptr)
		{
			instancedTmp->InstancedBufferInfo(tmptbo, tbolen);
			if(instancedTmp->lmodtb) this->BufferTBO( instancedTmp, tmptbo, tbolen, offsettbo);
			//offsettbo+=tmptbo*tbolen;
			// ?? Never Texted, this comment can be removed when two particle system are present at once
		}




	}
	}

}


Scene::~Scene()
{
	if(ldbgcolliders) delete collidersdebug;
}

void Scene::BufferVBO(VectorizedObject* obj,uint& tmpvbo, uint& vertxlen, uint& offsetvbo, uint& offsetvbover)
{

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glCheckError();
	//std::cout << offsetvbo << " " << tmpvbo*vertxlen << std::endl;

	glBufferSubData( GL_ARRAY_BUFFER, offsetvbo*sizeof(GLfloat), tmpvbo*vertxlen*sizeof(GLfloat), obj->vertex_buffer );


	GLenum error = glGetError();

	if(error!=GL_NO_ERROR)
	{
	printf("ERROR: Scene Prepare, Vertex Buffer Filling %s ", gl_error_string(error));
	throw std::exception();
	}


}

void Scene::BufferIBO(VectorizedObject* obj, uint& tmpibo, uint& offsetibo)
{
	int i=0,j=0;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
	glCheckError();
	glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, offsetibo*sizeof(GLuint), tmpibo*sizeof(GLuint), obj->index_buffer );


	GLenum error = glGetError();

	if(error!=GL_NO_ERROR)
	{
		printf("ERROR: Scene::Prepare-IBO filling: %s | AssetsProgram %d | AssetsProgramIndex %d\n", gl_error_string(error), i, j);
		throw std::exception();
	}

}

void Scene::BufferTBO(InstancedObject* obj,uint& tmptbo, uint& tbolen, uint& offsettbo)
{
        int i=0,j=0;
	glBindBuffer( GL_ARRAY_BUFFER, TBO );
	glCheckError();
	glBufferSubData( GL_ARRAY_BUFFER,
			  offsettbo*sizeof(GLfloat),
			  tmptbo*tbolen*sizeof(GLfloat),
			  obj->instance_buffer );


	GLenum error = glGetError();

	if(error!=GL_NO_ERROR)
	{
		printf("ERROR: Scene::Prepare-TBO filling: %s | AssetsProgram %d | AssetsProgramIndex %d\n",
		gl_error_string(error), i, j);
		throw std::exception();
	}

}
