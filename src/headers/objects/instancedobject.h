
#ifndef INSTANCEDOBJECT
#define INSTANCEDOBJECT
class  InstancedObject  : virtual public VectorizedObject
{	

	private:
		int  instance_num = 0;
		int  instance_len = 0;
	protected:
		void EnableTBOAttributes(GLuint TBO,GLuint& offsettbo);	
	public:
	
		float* instance_buffer = NULL;
		std::vector<std::string> instanceattributenames;
		std::vector<int> instanceattributesizes;
		std::vector<int> instanceattributelocationsprogram;
		std::vector<int> instanceattributedivisors;
		
		
		void InstancedBufferInfo(uint &TBOsize, uint &instance_len_ );
		void Render(GLuint VBO, GLuint IBO, GLuint TBO, GLuint& offsetvbo, GLuint& offsetibo, GLuint& offsettbo);
		int SpecifyBuffersInstanceAttributes(const std::string& name, int attributesize, int divisor);
		
		InstancedObject(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, 
				 int instances_num_, int instance_len_);
	
		~InstancedObject();
	
};


#endif
