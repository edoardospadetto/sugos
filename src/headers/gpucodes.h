#ifndef GPUCODES
#define GPUCODES


class GPUcodes
{
	
	private:
	
	Window_Class* parent = nullptr;
	
		
	public:
	
	const std::vector<std::string> types {"VERTEX" , "FRAGMENT"};

	std::string path;
	std::vector<std::string> shaders;
	std::vector<std::string> shaders_name;
	std::vector<std::string> programnames;
	std::vector<int> shaders_type;

	std::vector<GLuint> glprograms;
		

	void ParseRaw(std::string& path_);
	void SplitRawInput(std::string rawin_);
	void Compile();
	

	GPUcodes(Window_Class* parent_, std::string&& path_);
	GPUcodes(Window_Class* parent_, std::string& path_);

	void SetParentWindow(Window_Class* parent_);
	std::vector<GLuint> shaders_id;

	void Load(const std::string& name1, const std::string& name2, const std::string& name3  );
	void Load(std::string&& name1, std::string&& name2 , std::string&& name3  );
	void EnableProgram(const std::string& name);
	void EnableProgram(std::string&& name);
	void EnableProgram(uint programindex);

};

#endif
