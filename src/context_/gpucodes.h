#ifndef GPUCODES
#define GPUCODES

#include <string>
#include <vector>
#include "../include/SDL&OpenGL.h"
typedef unsigned int uint;
class Window_Class;

class GPUcodes
{
	
	private:
	
	Window_Class* parent = nullptr;
	std::string version; 
	bool lversion=false;
	void ForceShaderVersion(std::string& shader_);
	void SpecifyVersion(std::string& version_);
	void ParseRaw(const std::string& path_);
	void SplitRawInput(std::string rawin_);
	void Compile();
	
	
	public:
	
	const std::vector<std::string> types {"VERTEX" , "FRAGMENT"};

	std::string path;
	std::vector<std::string> shaders;
	std::vector<std::string> shaders_name;
	std::vector<std::string> programnames;
	std::vector<int> shaders_type;

	std::vector<GLuint> glprograms;
		

	

	GPUcodes(Window_Class* parent_, std::string&& path_);
	GPUcodes(Window_Class* parent_, std::string& path_);
	GPUcodes(Window_Class* parent_, const std::string& t, std::string version_ );
	~GPUcodes(){};

	void SetParentWindow(Window_Class* parent_);
	std::vector<GLuint> shaders_id;

	void Load(const std::string& name1, const std::string& name2, const std::string& name3  );
	void Load(std::string&& name1, std::string&& name2 , std::string&& name3  );
	void EnableProgram(const std::string& name);
	void EnableProgram(std::string&& name);
	void EnableProgram(uint programindex);
	
	
};

#endif
