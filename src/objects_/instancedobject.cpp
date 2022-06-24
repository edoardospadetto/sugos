#include "./instancedobject.h"
#include "../modules_/debugmisc_module.h"
//#include "../include/safe_include_SDLGL_OpenGL.h"


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

int InstancedObject::SpecifyBuffersInstanceAttributes(const std::string& name, int instanceattributesize_, int divisor_)
{
	instanceattributenames.push_back(name);
	instanceattributesizes.push_back(attributesizes[instanceattributesizes.size()-1]+instanceattributesize_);
	instanceattributelocationsprogram.push_back(-1);
	instanceattributedivisors.push_back(divisor_);
	
	return(instanceattributenames.size()-1);
}


void InstancedObject::EnableTBOAttributes(GLuint TBO,GLuint& offsettbo)
{

	glBindBuffer( GL_ARRAY_BUFFER, TBO );
	
	for(int k=0; k<this->instanceattributenames.size(); k++ )
	{
		
			
		glVertexAttribPointer(  this->instanceattributelocationsprogram[k], 
					(this->instanceattributesizes[k+1] - this->instanceattributesizes[k]), 
					GL_FLOAT, 
					GL_FALSE, 
					(this->instanceattributesizes[this->instanceattributesizes.size()-1])*sizeof(GLfloat), 
					(void*) ((offsettbo+this->instanceattributesizes[k])*sizeof(GLfloat)) );
				

		glCheckError();
		glVertexAttribDivisor(this->instanceattributelocationsprogram[k], this->instanceattributedivisors[k]);
		glCheckError();
		glEnableVertexAttribArray(this->instanceattributelocationsprogram[k]);
		glCheckError();
	}


}


void InstancedObject::Render(GLuint VBO, GLuint IBO, GLuint TBO, GLuint& offsetvbo, GLuint& offsetibo, GLuint& offsettbo)
{
	
		
	
	
		this->RenderProgramUniforms();
		glCheckError();
		
		this->EnableVBOAttributes(VBO, offsetvbo);
		glCheckError();
		
		this->EnableTBOAttributes(TBO,offsettbo);
		glCheckError();
			
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
		
	
		this->UnbindTexture();
		glCheckError();
		
		int nbuffersize, vbsi; 
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &nbuffersize);
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vbsi);
		glCheckError();	

		offsetibo += this->surfaces_num*this->vertexxsurf;
		offsetvbo += this->vertex_num*this->vertex_len;
		offsettbo+=  this->instance_num * this->instance_len;
		
		for(int k=0; k<this->attributenames.size(); k++ ){glDisableVertexAttribArray( this->attributelocationsprogram[k]);}
		for(int k=0; k<this->instanceattributenames.size(); k++ )
		{glDisableVertexAttribArray( this->instanceattributelocationsprogram[k]);}	
		glCheckError();

}
/*
void ModTB(int idx, float val)
{
	lmodtb=true;
	this->instance_buffer[idx]=val;

}

*/
