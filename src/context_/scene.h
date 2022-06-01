

/*
* A scene is everything that is on screen now and on the near future.
* It hangles all the call to OpenGL given the objects it has to draw.
*/
#include <vector>

class Window_Class;
class GPUcodes;
#include "../engines_/collisionengine.h"
class VectorizedObject2D;
class ColliderObject2D;

class Scene
{
	private: 
		
	
	        Window_Class* parent = nullptr;
		bool ldbgcolliders = false;
		CollisionEngine sceneCollisionEngine;
		
		GLuint VBO = 0;
		GLuint IBO = 0;
		//Instanced
		GLuint TBO = 0;
		
		uint vertexbuffersize=0, indexbuffersize=0, instancebuffersize=0;
		std::vector<std::vector<VectorizedObject*>> assets;
		std::vector<GLuint> programs;
		
		GLuint collidersdbg_pragma;
		GPUcodes *collidersdebug = nullptr;
	
	public:
	
		Scene();		 
		void Render();
		void SetCollisionHandler(void (*CollisionHandler_)(std::vector<ColliderObject2D*>&, std::vector<int>&, glm::vec2*, float* ) );
		void LoadObj(VectorizedObject& obj, GLuint designatedprogram);
		void Prepare();
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
