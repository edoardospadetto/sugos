
#ifndef INSTANCEDOBJECT
#define INSTANCEDOBJECT
class  InstancedObject  : virtual public VectorizedObject
{	

	private:
		int  instance_num = 0;
		int  instance_len = 0;
		
	public:
	
	
		std::vector<std::string> instanceattributenames;
		std::vector<int> instanceattributesizes;
		std::vector<int> instanceattributelocationsprogram;
	
	
		float* instance_buffer = NULL;
		
		void InstancedBufferInfo(uint &TBOsize, uint &instance_len_ );
		void Render(GLuint VBO, GLuint IBO, GLuint TBO, GLuint& offsetvbo, GLuint& offsetibo, GLuint& offsettbo);
		int SpecifyBuffersInstanceAttributes(const std::string& name, int attributesize);
		
		InstancedObject(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, 
				 int instances_num_, int instance_len_);
	
		~InstancedObject();
	
};


#endif
