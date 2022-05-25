#include "../../turtle.h" 


InstancedObject::InstancedObject(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_, 
				 int instance_num_, int instance_len_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_), 
instance_num(instance_num_),
instance_len(instance_len_)
{
	instance_buffer = new float[ instance_num_* instance_len_];
	instanceattributesizes.push_back(0);
}


void InstancedObject::InstancedBufferInfo(uint &TBOsize, uint &instance_len_ )
{
	TBOsize    = instance_num;
	instance_len_ = instance_len;	
}

InstancedObject::~InstancedObject()
{
	delete [] instance_buffer;

}

int InstancedObject::SpecifyBuffersInstanceAttributes(const std::string& name, int instanceattributesize_)
{
	instanceattributenames.push_back(name);
	instanceattributesizes.push_back(attributesizes[instanceattributesizes.size()-1]+instanceattributesize_);
	instanceattributelocationsprogram.push_back(-1);

	return(instanceattributenames.size()-1);
}



void InstancedObject::Render(GLuint VBO, GLuint IBO, GLuint TBO, GLuint& offsetvbo, GLuint& offsetibo, GLuint& offsettbo)
{
	
		
	
		uint tmpibo = 0, tmpvbo = 0, tmptbo = 0; 
		this->RenderProgramUniforms();
		glCheckError();
		this->GetBuffersInfo(tmpvbo, tmpibo);	
		glCheckError();
		
		glBindBuffer( GL_ARRAY_BUFFER, VBO );
		for(int k=0; k<this->attributenames.size(); k++ )
		{
			
			glVertexAttribPointer(  this->attributelocationsprogram[k], 
						(this->attributesizes[k+1] - this->attributesizes[k]), 
						GL_FLOAT, 
						GL_FALSE, 
						(this->attributesizes[this->attributesizes.size()-1])*sizeof(GLfloat), 
						(void*) ((offsetvbo+this->attributesizes[k])*sizeof(GLfloat)) );
			glVertexAttribDivisor(this->instanceattributelocationsprogram[k], 1);
			glEnableVertexAttribArray(this->attributelocationsprogram[k]);
			
		        glCheckError();

		}	
		glBindBuffer( GL_ARRAY_BUFFER, TBO );
		for(int k=0; k<this->instanceattributenames.size(); k++ )
		{
		
			/*std::cout << this->instanceattributelocationsprogram[k] << " h " 
				  << (this->instanceattributesizes[k+1] - this->instanceattributesizes[k]) << " h "
				  << (this->instanceattributesizes[this->instanceattributesizes.size()-1])*sizeof(GLfloat) << " h "
				  << (void*) ((offsettbo+this->instanceattributesizes[k])*sizeof(GLfloat)) ;*/
			
			glVertexAttribPointer(  this->instanceattributelocationsprogram[k], 
						(this->instanceattributesizes[k+1] - this->instanceattributesizes[k]), 
						GL_FLOAT, 
						GL_FALSE, 
						(this->instanceattributesizes[this->instanceattributesizes.size()-1])*sizeof(GLfloat), 
						(void*) ((offsettbo+this->instanceattributesizes[k])*sizeof(GLfloat)) );
						
			/*std::cout << (this->instanceattributesizes[k+1] - this->instanceattributesizes[k]) << "  "
			          << (offsetvbo+this->instanceattributesizes[k]) << "  "
			          << this->instanceattributesizes[this->instanceattributesizes.size()-1] << "  " 
			          << this->instanceattributesizes.size()<< "\n";*/
			glCheckError();
			//
			glEnableVertexAttribArray(this->instanceattributelocationsprogram[k]);
			
		        glCheckError();
		}
		
		
			
	  	this->RenderTexture();
		glCheckError();
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
		glCheckError();
		glDrawElementsInstanced( this->representation , 
				this->surfaces_num*this->vertexxsurf, 
				GL_UNSIGNED_INT, 
				(void*) (offsetibo*sizeof(GLuint)), 
				this->instance_num );
		glCheckError();
		int nbuffersize, vbsi; 
		this->UnbindTexture();
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &nbuffersize);
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vbsi);
		glCheckError();	

		offsetibo +=this->surfaces_num*this->vertexxsurf;
		offsetvbo += tmpvbo*this->vertex_len;
		offsettbo+=  this->instance_num * this->instance_len;
		for(int k=0; k<this->attributenames.size(); k++ ){glDisableVertexAttribArray( this->attributelocationsprogram[k]);}
		for(int k=0; k<this->instanceattributenames.size(); k++ )
		{glDisableVertexAttribArray( this->instanceattributelocationsprogram[k]);}	
		glCheckError();

}

