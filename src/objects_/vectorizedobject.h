
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
#include <string>
#include <vector>

#include "../include/SDL&OpenGL.h"

class VectorizedObject
{
	protected:
	
	void GetBuffersInfo(uint& sizevbo,uint& sizeibo);
	void RenderProgramUniforms();
	void EnableVBOAttributes(GLuint VBO, GLuint& offsetvbo);
	bool hidden=false;	
	public:

	// Physics
	float                          angle = 0.0;
	float*				position = NULL; 
	
	
	//Buffers 
	float*				vertex_buffer = NULL;
	int* 				index_buffer = NULL;
	
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
	int vertex_len = 0;
	int vertex_num = 0;
	int surfaces_num = 0;
	int space_dim = 0; 
	
	//Temp
	int sceneprog=0; 
	int sceneprogidx =0;

	virtual void Render(GLuint VBO, GLuint IBO, GLuint& offsetvbo, GLuint& offsetibo);


	int vertexxsurf = 0;
	
	
	VectorizedObject(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,GLenum representation_);
	~VectorizedObject();
	
	
	void GetBuffersInfo(uint& sizevbo,uint& sizeibo, uint& vtlen);


	void SetToOrigin(int vblocation);
	void Translate(int vblocation,float* val);
	void Rescale(int vblocation, float factor);

	
	int LinkUniformToVariable(std::string&& uniformname, int uniformsize );
	int LinkUniformToVariable(const std::string& uniformname, int uniformsize);
	
	int SpecifyBuffersAttributes(std::string&& name, int size);
	int SpecifyBuffersAttributes(const std::string& name, int size);

	int SetUniform(const std::string& uniformname,int idx, float value);
	int SetUniform(std::string&& uniformname,int idx, float value);
	void SetUniform(int uniformidx,int idx, float value);
	
	void Hide();
	void Show();
	virtual void RenderTexture() ;
	virtual void UnbindTexture() {};

};

#endif
