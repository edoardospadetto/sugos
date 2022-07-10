#ifndef GPUCODES
#define GPUCODES

#include <string>
#include <vector>
#include "../include/safe_include_SDLGL_OpenGL.h"
typedef unsigned int uint;
class Window_Class;

class GPUcodes
{
	
	private:
	
	Window_Class* parent = nullptr;
	std::string version; 
	bool lversion=false;
	void ForceShaderVersion(std::string& shader_);
	void ParseRaw(const std::string& path_);
	void SplitRawInput(std::string rawin_);
	int  CompileIdx(int idx);
	int  Compile(const char* source, GLenum shaderType, GLint& id );
	void Link(int idxV, int idxF, const std::string& programName);
	void CombineFunction(std::string& body, int idx_f, int idx_temp );
   
	
	int FindNameIndex(const std::string& name);
	
	public:
	
	const std::vector<std::string> types {"VERTEX" , "FRAGMENT"};
	
	//Following 3 push_back'ed in ParseInput
	std::vector<std::string> shaders;
	std::vector<std::string> shaders_name;
	std::vector<int> shaders_type;
	//Following 2 push_back'ed in Compile
	std::vector<GLuint> shaders_id;
	//std::vector<std::vector<int>> shader_id_to_idxs; to not compile twice
	
	//Following 2 push_back'ed in Load
	std::vector<std::string> programnames;
	std::vector<GLuint> glprograms;
		

	
    GPUcodes(Window_Class* parent_); //1
    
	GPUcodes(Window_Class* parent_, std::string&& path_);
	GPUcodes(Window_Class* parent_, std::string& path_);
	GPUcodes(Window_Class* parent_, const std::string& t, std::string version_ );
	~GPUcodes(){};
    
	void SetParentWindow(Window_Class* parent_);
    void SpecifyVersion(std::string& version_);
    void SpecifyVersion(std::string&& version_);
    void PrintSummary();
    void AddSource(const std::string& path_); //2
    void Load(std::initializer_list<std::string>&& combinedVertex,std::initializer_list<std::string>&& combinedFragment, std::string&& programName  );
    void Load(const std::initializer_list<std::string>& combinedVertex,
              const std::initializer_list<std::string>& combinedFragment, const std::string& programName);
	void Load(const std::string& name1, const std::string& name2, const std::string& name3  );
	void Load(std::string&& name1, std::string&& name2 , std::string&& name3  );
	void EnableProgram(const std::string& name);
	void EnableProgram(std::string&& name);
	void EnableProgram(uint programindex);
	
	
};

#endif
