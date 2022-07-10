

/*
* A scene is everything that is on screen now and on the near future.
* It hangles all the call to OpenGL given the objects it has to draw.
*/
#include <vector>
#include "../engines_/collisionengine.h"

class Window_Class;
class GPUcodes;
class VectorizedObject2D;
class ColliderObject2D;
class InstancedObject;
class Scene
{
	private: 
	
	
		void BufferVBO(VectorizedObject* obj,uint& tmpvbo, uint& vertxlen, uint& offsetvbo, uint& offsetvbover);
		void BufferTBO(InstancedObject* obj,uint& tmptbo, uint& tbolen, uint& offsettbo);
		void BufferIBO(VectorizedObject* obj, uint& tmpibo, uint& offsetibo);
		
		std::vector<std::string> GetVarNamesFromShader(GLuint designatedprogram, GLenum kind);
		
		void LoadShaderVars(std::vector<std::string>& objAtrbNames,std::vector<int>& atrbLocs, 
			       GLuint designatedprogram, std::vector<std::string>& atrbNames, GLint kind );
			              
	
		void CheckAnyForgottenVar(std::vector<std::string>& varNames );
		
		
	        Window_Class* parent = nullptr;
		bool ldbgcolliders = false;
		CollisionEngine sceneCollisionEngine;
		
		GLuint VBO = 0;
		
		GLuint IBO = 0;
		//Instanced
		GLuint TBO = 0;
		
		uint vertexbuffersize=0;
		uint indexbuffersize=0; 
		uint instanceBufferSize=0;
		std::vector<std::vector<VectorizedObject*>> assets;
		std::vector<GLuint> programs;
		
		GLuint collidersdbg_pragma;
		GPUcodes *collidersdebug = nullptr;
	
	public:
	
		Scene();	
		void ReBuffer();	 
		void Render();
		void SetCollisionHandler(void (*CollisionHandler_)(std::vector<ColliderObject2D*>&, std::vector<int>&, glm::vec2*, float* ) );
		void LoadObject(VectorizedObject* obj, GLuint designatedprogram);
		void Prepare();
		void PrepareAdd();
		void ProgramUniforms(VectorizedObject* obj);
		void UnloadObject(VectorizedObject& obj);
		void Collisions();
		void DebugColliders(Window_Class* parent);
		void Update();
		void Animations();
		void Physics();
		
		
		~Scene();
};
// TO DO
//void Scene::Renovate()
/* PURPOSE
* if parts of the CPU buffers are modified
* this function through a system to keep track of it
* should buffersubdata only the modified parts
* and not create a new buffer.
*
*/
