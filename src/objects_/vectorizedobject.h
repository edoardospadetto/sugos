
//VectorizedObject

/* 
* This is the most basic type of object appearing on screen.
* 
* Buffers
* std::vector<std::string>  buffernames
* Names given to each buffer,
*
*/

#ifndef VECTORIZEDOBJECT
#define VECTORIZEDOBJECT
typedef unsigned int uint;
#include <stdint.h>
#ifdef EMSCRIPTEN_MACRO
#include <emscripten.h>
#endif
#include <string>
#include <vector>

#include "../include/safe_include_SDLGL_OpenGL.h"
#include "../attributes_/texture.h"

class VectorizedObject
{
	protected:
	
		VectorizedObject(){};
		void Init();
		void Fill(int vertex_len_,int vertex_num_, int surfaces_num_, int space_dim_,GLenum representation_);
		void GetBuffersInfo(uint& sizevbo,uint& sizeibo);
		void RenderProgramUniforms();
		void EnableVBOAttributes(GLuint VBO, GLuint& offsetvbo);
		Texture* pTexture = nullptr;
		bool hidden=false;
		
		virtual void Render(GLuint VBO, GLuint IBO, GLuint& offsetvbo, GLuint& offsetibo);
		virtual void RenderTexture() {if(pTexture) pTexture->RenderTexture();};
		virtual void UnbindTexture() {if(pTexture) pTexture->UnbindTexture();};
		
		
		bool lmodib;
		bool lmodvb;
		
		std::vector<std::string>	buffernames = {};
		std::vector<int> 		buffersizes = {};
		std::vector<int> 		bufferformat = {};
		
		// Uniforms
		std::vector<float> 		uniformattributes = {}; 
		std::vector<std::string> 	uniformnames ={};
		std::vector<int> 		uniformlocationsprogram ={};
		std::vector<int> 		uniformsizes ={};
		
		//IBO & VBO vars
		std::vector<std::string> attributenames={}; 
		std::vector<int> attributelocationsprogram={};
		GLenum representation = -1;
		std::vector<int> attributesizes={};
		
		//Geometry Info
		int vertexxsurf = 0;
		int vertex_len = 0;
		int vertex_num = 0;
		int surfaces_num = 0;
		int space_dim = 0; 
		
		//Temp
		int sceneprog=0; 
		int sceneprogidx =0;
		
	
	
	public:

	// Physics
	float                          angle = 0.0;
	float*				position = NULL; 
	
	
	//Buffers 
	float*				vertex_buffer = NULL;
	int* 				index_buffer = NULL;
	
	
	/**
	* @brief Computes the average of the two passed values.
	*
	* This function computes the average using the standard accepted
	* formula for doing so.
	*
	* @return The average of the two passed values.
	* @param x The first value to average.
	* @param y The second value to average.
	* @todo Need to write acceptance tests for this function
	*/

	VectorizedObject(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,GLenum representation_);
	
	
	void GetBuffersInfo(uint& sizevbo,uint& sizeibo, uint& vtlen);


	void SetToOrigin(int vblocation);
	void Translate(int vblocation,float* val);
	void Rescale(int vblocation, float factor);

	
	int LinkUniformToVariable(std::string&& uniformname, int uniformsize );
	int LinkUniformToVariable(const std::string& uniformname, int uniformsize);
	
	
	void ModIB(int idx, int val);
	void ModVB(int idx, float val);
	

	int SpecifyBuffersAttributes(std::string&& name, int size);
	int SpecifyBuffersAttributes(const std::string& name, int size);

	int SetUniform(const std::string& uniformname,int idx, float value);
	int SetUniform(std::string&& uniformname,int idx, float value);
	void SetUniform(int uniformidx,int idx, float value);
	void SetTexture(Texture* texture_);
	
	
	~VectorizedObject();
	
	
	void Hide();
	void Show();

	
	friend class Scene;

};

#endif
