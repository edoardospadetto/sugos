#include <algorithm>
#include "./vectorizedobject.h"

#include "../modules_/debugmisc_module.h"



void VectorizedObject::Fill(int vertex_len_,int vertex_num_, int surfaces_num_, int space_dim_,GLenum representation_)
{

	vertex_len =  vertex_len_;
	vertex_num = vertex_num_;
	surfaces_num = surfaces_num_;
	space_dim = space_dim_;
	representation = representation_;
}


void VectorizedObject::Init()
{

	dbglog("============= Object ============");
	dbglog("vertex length   = ", vertex_len );
	dbglog("vertex number   = ", vertex_num );
	dbglog("surfaces number = ", surfaces_num );


	switch(representation)
	{
		case GL_LINES:
	 		vertexxsurf = 2;
	 		break;
	 	case GL_TRIANGLES:
	 		vertexxsurf = 3;
	 		break;


#ifdef OPENGL_MACRO
		 case GL_QUADS:
	 		vertexxsurf = 4;
	 		std::cout << "Warnig :: GLQUADS" << std::endl;
	 		break;
#endif

	}
	position      = new float[space_dim];


	vertex_buffer = new float[vertex_len*vertex_num];
	index_buffer  = new int[surfaces_num*vertexxsurf];
	uniformsizes.push_back(0);
	attributesizes.push_back(0);
}

VectorizedObject::VectorizedObject(int vertex_len_,int vertex_num_, int surfaces_num_, int space_dim_,GLenum representation_):
vertex_len( vertex_len_), vertex_num(vertex_num_),  surfaces_num(surfaces_num_), space_dim(space_dim_), representation(representation_)
{

	this->Init();
}

void VectorizedObject::GetBuffersInfo(uint &VBOsize , uint &IBOsize, uint &vertexlen_ )
{
	VBOsize    = vertex_num;
	IBOsize    = vertexxsurf*surfaces_num;
	vertexlen_ = vertex_len;
}

void VectorizedObject::GetBuffersInfo(uint &VBOsize , uint& IBOsize )
{
	VBOsize = vertex_num;
	IBOsize= vertexxsurf*surfaces_num;
}

// Routine to rescale object, suggested to use after resetting to origin
void  VectorizedObject::Rescale(int vblocation,float factor)
{
for (int i=0; i<vertex_num; i++){for(int j=0; j<space_dim; j++)
{
		vertex_buffer[ i*vertex_len + vblocation +j ] *= factor;
}}


}

// Set center of mass of object to center of coordinate system
// vb location is the offster of the coordinates on the buffer.
// coordinates are supposed subsequential.
void VectorizedObject::SetToOrigin(int vblocation)
{
	if(vertex_buffer == nullptr) printf("ERROR: nullptr vertex buffer\n");

	for (int i=0; i<space_dim; i++){position[i] = 0.0;}

	for (int i=0; i<vertex_num; i++){for(int j=0; j<space_dim; j++)
	{
			position[j] += vertex_buffer[ i*vertex_len + vblocation +j ];
	}}

	for (int i=0; i<space_dim; i++) {position[i] = position[i] / float(vertex_len);}


	for (int i=0; i<vertex_num; i++){for(int j=0; j<space_dim; j++)
	{
			vertex_buffer[ i*vertex_len + vblocation +j ] -= position[j];
	}}

}

void VectorizedObject::Translate(int vblocation,float* val)
{
	if(vertex_buffer == nullptr) printf("ERROR: nullptr vertex buffer\n");


	for (int i=0; i<vertex_num; i++){for(int j=0; j<space_dim; j++)
	{
			vertex_buffer[ i*vertex_len + vblocation +j ] += val[j];
	}}

}

VectorizedObject::~VectorizedObject()
{

	delete [] index_buffer;
	delete [] vertex_buffer;
	if ( position != nullptr ) delete[] position;


}
int VectorizedObject::LinkUniformToVariable(std::string&& uniformname, int uniformsize , GLenum kind)
{
	return LinkUniformToVariable( uniformname, uniformsize,kind );
}

int VectorizedObject::LinkUniformToVariable(const std::string& uniformname, int uniformsize, GLenum kind )
{
	if ( std::find(uniformnames.begin(), uniformnames.end(), uniformname) != uniformnames.end() )
	{
	    printf("Warning, uniform already binded, skip operation (if necessary change name)\n");
	}
	else
	{
	    for(int i=0; i<uniformsize; i++){ uniformattributes.push_back(0.0);}
	    uniformnames.push_back(uniformname);
	    uniformkinds.push_back(kind);
	    uniformlocationsprogram.push_back(-1);
	    uniformsizes.push_back(uniformsize+uniformsizes[uniformsizes.size()-1]);
	    return(uniformnames.size()-1);
    }
}
int VectorizedObject::SetUniform(const std::string& uniformname,int idx, float value)
{

	for (int i=0; i<uniformnames.size(); i++)
	{

		if(uniformname == uniformnames[i]){
			 if(idx<uniformsizes[i+1]-uniformsizes[i] & idx >= 0){uniformattributes[uniformsizes[i]+idx] = value;	return(i);}
			 else{printf("ERROR, invalid index for the requested uniform %d %s \n", uniformsizes[i+1]-uniformsizes[i], uniformnames[i].c_str());}

		}
	}
	printf("ERROR, uniform not found\n");
	return(-1);
}







int VectorizedObject::SetUniform(std::string&& uniformname,int idx, float value) {return SetUniform(uniformname,idx,value);}
void VectorizedObject::SetUniform(int uniformidx,int idx, float value)
{
	uniformattributes[uniformsizes[uniformidx]+idx] = value;
}







int VectorizedObject::SpecifyBuffersAttributes(std::string&& name, int size){return SpecifyBuffersAttributes(name, size);}





int VectorizedObject::SpecifyBuffersAttributes(const std::string& name, int attributesize)
{
	attributenames.push_back(name);
   attributeskip.push_back(false);
	attributesizes.push_back(attributesizes[attributesizes.size()-1]+attributesize);
	attributelocationsprogram.push_back(-1);

	return(attributenames.size()-1);
}

int VectorizedObject::SkipAttribute(size_t idx){
   if(idx >=0 && idx<this->attributeskip.size() )
   {
      this->attributeskip[idx] = true;
      return(0);
   } else {
      return(this->attributeskip.size());
   }
}

int VectorizedObject::UnSkipAttribute(size_t idx){
   if(idx >=0 && idx<this->attributeskip.size() )
   {
      this->attributeskip[idx] = true;
      return(0);
   } else {
      return(this->attributeskip.size());
   }
}


void VectorizedObject::EnableVBOAttributes(GLuint VBO, GLuint& offsetvbo)
{
	uint tmpvbo = this->vertex_num;

	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	for(int k=0; k<this->attributenames.size(); k++ )
	{
      if(this->attributeskip[k]) continue;
      
		glVertexAttribPointer(  this->attributelocationsprogram[k],
					(this->attributesizes[k+1] - this->attributesizes[k]),
					GL_FLOAT,
					GL_FALSE,
					(this->attributesizes[this->attributesizes.size()-1])*sizeof(GLfloat),
					(void*) ((offsetvbo+this->attributesizes[k])*sizeof(GLfloat)) );
		glEnableVertexAttribArray(this->attributelocationsprogram[k]);
		//glVertexAttribDivisor(this->instanceattributelocationsprogram[k], divisor[k]);
		glCheckError();

	}

}

void VectorizedObject::Render(GLuint VBO, GLuint IBO, GLuint& offsetvbo, GLuint& offsetibo)
{



		if(!hidden)
		{
			this->RenderProgramUniforms();
			glCheckError();
			this->EnableVBOAttributes(VBO, offsetvbo);
			glCheckError();
		  	this->RenderTexture();
			glCheckError();

			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IBO );
			glCheckError();

			glDrawElements( this->representation ,
					this->surfaces_num*this->vertexxsurf,
					GL_UNSIGNED_INT,
					(void*) (offsetibo*sizeof(GLuint)) );

			glCheckError();
			int nbuffersize, vbsi;
			this->UnbindTexture();
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &nbuffersize);
			glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &vbsi);
			glCheckError();


			for(int k=0; k<this->attributenames.size(); k++ ){glDisableVertexAttribArray( this->attributelocationsprogram[k]);}
			glCheckError();
		}
			offsetibo +=this->surfaces_num*this->vertexxsurf;
			offsetvbo += this->vertex_num*this->vertex_len;
}

void VectorizedObject::Hide()
{
	this->hidden=true;
}
void VectorizedObject::Show()
{
	this->hidden=false;
}

void VectorizedObject::RenderProgramUniforms()
{

	for(int k=0; k< this->uniformnames.size(); k++)
	{
	    if(uniformkinds[k] == GL_FLOAT)
	    {
		    switch(this->uniformsizes[k+1]-this->uniformsizes[k])
		    {

			    case 1:
			        glUniform1f(this->uniformlocationsprogram[k],
				    this->uniformattributes[this->uniformsizes[k]]);
				    break;
			    case 2:
				    glUniform2f(this->uniformlocationsprogram[k],
				    this->uniformattributes[this->uniformsizes[k]],
				    this->uniformattributes[this->uniformsizes[k]+1]);
				    break;
			    case 3:
				    glUniform3f(this->uniformlocationsprogram[k],
				    this->uniformattributes[this->uniformsizes[k]],
				    this->uniformattributes[this->uniformsizes[k]+1],
				    this->uniformattributes[this->uniformsizes[k]+2]);
				    break;
			    case 4:
				    glUniform4f(this->uniformlocationsprogram[k],
				    this->uniformattributes[this->uniformsizes[k]],
				    this->uniformattributes[this->uniformsizes[k]+1],
				    this->uniformattributes[this->uniformsizes[k]+2],
				    this->uniformattributes[this->uniformsizes[k]+3]);
				    break;
			    case 16:
			        glUniformMatrix4fv( this->uniformlocationsprogram[k],
                                        1,
                                        false,
                                        &(this->uniformattributes[this->uniformsizes[k]]));
			        break;
				    //dbglog("unif" , obj->uniformattributes[obj->uniformsizes[k]],obj->uniformattributes[obj->uniformsizes[k]+1 ]);
		    }
		}
		else if (uniformkinds[k] == GL_INT)
	    {
            switch(this->uniformsizes[k+1]-this->uniformsizes[k])
            {

                case 1:
                    glUniform1i(this->uniformlocationsprogram[k],
                    this->uniformattributes[this->uniformsizes[k]]);
                    break;
            }

	    }
	}


}



void VectorizedObject::SetTexture(Texture* texture_)
{
	pTextures.push_back(texture_);
	texture_idx.push_back(texture_idx.size());
	std::cout << __FILE__<<":"<<__LINE__<< " " << __FUNCTION__<< " is deprecated\n";
	//throw std::exception();
	//pTexture = texture_;
}

void VectorizedObject::SetTexture(Texture* texture_, std::string&& name)
{
   pTextures.push_back(texture_);
   this->LinkUniformToVariable(name,1, GL_INT);
   texture_idx.push_back(texture_idx.size());
   this->SetUniform(name, 0, texture_idx.size()-1);
}



void VectorizedObject::RenderTexture()
{

    for (int i=0; i < pTextures.size() ; i++)
    {

        pTextures[i]->RenderTexture(texture_idx[i]);

    }
    //pTexture->RenderTexture();
}
void VectorizedObject::UnbindTexture()
{

    for (auto txtr=pTextures.begin(); txtr!=pTextures.end(); txtr++)
    {
        (*txtr)->UnbindTexture();
    }
    //pTexture->UnbindTexture();

}


/*

void ModIB(int idx, int val)
{

}

void ModVB(int idx, float val)
{

}

*/
