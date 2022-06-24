#include "./gpucodes.h" 
#include "../context_/window.h"
#include "../modules_/debugmisc_module.h"
#include <fstream>
#include <cstdio>


//#include "../include/safe_include_SDLGL_OpenGL.h"


void GPUcodes::ParseRaw(const std::string& path_)
{
	dbglog(" ===================================== ");
	dbglog(" =======      SHADER SUMMARY    ====== ");
	dbglog(" ===================================== ");

	std::string source;	
	std::ifstream buffer(path_,std::ios::binary|std::ios::ate);
	if (!buffer) 
	{
		printf("ERROR: Failed to open :%s  \n ", path_.c_str());
	} 
	else 
	{
		
	  int length = buffer.tellg();
	 
  	  buffer.seekg(std::ios::beg);
  	  source.resize(length,0);
  	 
  	  buffer.read(&source[0],length);
	
	}
	SplitRawInput(source);
	//printf(source);

}

GPUcodes::GPUcodes(Window_Class* parent_, std::string&& t): parent(parent_) {parent->MakeCurrent();ParseRaw(t);Compile();}
GPUcodes::GPUcodes(Window_Class* parent_, std::string& t): parent(parent_) {parent->MakeCurrent();ParseRaw(t);Compile();}
GPUcodes::GPUcodes(Window_Class* parent_, const std::string& t, std::string version_ ): parent(parent_) 
{	parent->MakeCurrent();
	this->SpecifyVersion(version_);
	ParseRaw(t);
	Compile();
}


void GPUcodes::SetParentWindow(Window_Class* parent_) {parent = parent_;} 

void GPUcodes::SpecifyVersion(std::string& version_)
{
	int delimiter1=version_.find("#version");
	if(delimiter1==-1)
	{
		printf("Error, format of version should be: #version <version>\n");
		throw 	std::exception(); 
	} 
	else 
	{
		std::cout << "delimiter 1 " << delimiter1 << "\n";
	}
	
	this->version=version_;
	this->lversion=true;
}

void GPUcodes::ForceShaderVersion(std::string& shader_)
{
	int delimiter1=shader_.find("#version");	
	if(delimiter1!=-1)
	{
		int delimiter2=shader_.find('\n', delimiter1+1);
		shader_= version + shader_.substr(delimiter2,shader_.length()-delimiter2);
		std::cout << shader_ << "\n";
		
	}
	else 
	{
		std::cout << "delimiter 1 " << delimiter1 << "\n";
	}
	
}

void GPUcodes::SplitRawInput(std::string rawin)
{
		
		int num_shader = countsubstr(rawin, "SHADER");
		int num_endshader = countsubstr(rawin, "ENDSHADER");	
		
		if (num_shader/2 != num_endshader)
		{
			printf("ERROR: Inconsistent Shader Sintax\n Decorate each shader with\n\n SHADER TYPE NAME\n {--code--}\n ENDSHADER\n,  ");	
		}	

		for (int i=0; i<num_endshader; i++)
		{
			int pos1=rawin.find("SHADER"), pos2=rawin.find("ENDSHADER");
			std::string fulldata = rawin.substr(pos1,pos2-pos1-1);
			
			int delimiter1=fulldata.find(' ');
			int delimiter2=fulldata.find(' ', delimiter1+1);
			int delimiter3=fulldata.find('\n', delimiter2+1);
			if(fulldata.find(' ', delimiter2+1) < delimiter3 )
			{
				delimiter3=fulldata.find(' ', delimiter2+1);
			}
			std::string type   = fulldata.substr(delimiter1+1,delimiter2-delimiter1-1);
			std::string shader = fulldata.substr(delimiter3+1,pos2-delimiter3-1);
			std::string name   = fulldata.substr(delimiter2+1,delimiter3-delimiter2-1);
			
			if(lversion) this->ForceShaderVersion(shader);

			shaders.push_back(shader);
			shaders_name.push_back(name);
		
			if(type == "VERTEX") 
			{
					shaders_type.push_back(GL_VERTEX_SHADER);
					type = type+"  ";
			}		
			else if(type == "FRAGMENT")
			{
					shaders_type.push_back(GL_FRAGMENT_SHADER);
			}
			else
			{
					shaders_type.push_back(-1);
			}

			dbglog(" ",i, " | ", shaders_type[i]," | ", type , " | " , shaders_name[i] );
			
			rawin = rawin.substr(pos2+1);
		
		}

		
}


void GPUcodes::Compile()
{

	dbglog("\n Compiling Shaders...");

	
   	for (int i =0 ; i<shaders.size() ; i++)
	{	
		/*dbglog("========================================");
		dbglog("---------- SHADER ", i , "------------");
		dbglog("----------------------------------------");
		dbglog(shaders[i]);
		dbglog("----------------------------------------");*/
		const char *shader_input =  shaders[i].c_str();
		
		GLuint id = glCreateShader(shaders_type[i]);
		
		//shaders_type.push_back(id);
		
		glShaderSource( id, 1 , &shader_input , NULL);
		glCompileShader(id);

		GLint status = GL_FALSE;
		glGetShaderiv( id, GL_COMPILE_STATUS, &status );
						

		if( status != GL_TRUE )
		{   
			if(glIsShader( id )) 
			{
				int length;	
				glGetShaderiv( id, GL_INFO_LOG_LENGTH, &length);
				char* info = new char[ length ];
				printf( "ERROR : Unable to compile Shader %d, type %s name %s \n", i, types[shaders_type[i]].c_str(), shaders_name[i].c_str() );
				glGetShaderInfoLog( id, length, &length, info );
				printf("%s", info);
				delete[] info ;
				throw std::exception();
			 }
			 else {printf("ERROR : Invalid Input for Shader %d, type %s name %s \n", i, types[shaders_type[i]].c_str(), shaders_name[i].c_str() );}
			  
		}
		else
		{
			shaders_id.push_back(id);
			dbglog(" SUCCESSFULL  ", shaders_name[i], shaders_id[i]);
			//dbglog("========================================");
		}   
		
	}

	
	
	
}

void GPUcodes::Load(std::string&& vertexname, std::string&& fragmentname, std::string&& programname  )
{

	Load(vertexname,fragmentname, programname);
}

void GPUcodes::Load(const std::string& vertexname, const std::string& fragmentname, const std::string& programname )
{
	parent->MakeCurrent();
	bool found1 = false,found2 = false ;
	GLuint program =  glCreateProgram();
	dbglog("\n Load Shaders...");


	for (int i=0; i<shaders.size(); i++)
	{
		if(shaders_type[i] ==  GL_VERTEX_SHADER)
		{
			if(shaders_name[i] == vertexname)
			{
					glAttachShader(program, shaders_id[i]);
					dbglog(" SUCCESSFULL  ", shaders_name[i], shaders_id[i]);
					found1 = true;
					
			}

		}
	}	
	if(!found1) printf("ERROR: Shader GLTYPE VERTEX , name |%s| not found. No shader in use.\n",vertexname.c_str());

	for (int i=0; i<shaders.size(); i++)
	{	
		
		if(shaders_type[i] == GL_FRAGMENT_SHADER)
		{
			if(shaders_name[i] == fragmentname)
			{
					glAttachShader(program, shaders_id[i]);
					dbglog(" SUCCESSFULL  ", shaders_name[i], shaders_id[i]);
					found2 = true;
					
			}

		}
	}
	if(!found2) printf("ERROR: Shader GLTYPE FRAGMENT , name |%s| not found. No shader in use.\n",fragmentname.c_str());

	if(found1 & found2) glprograms.push_back(program); programnames.push_back(programname); glLinkProgram(program);
	
	GLint programSuccess = GL_TRUE;
        glGetProgramiv( program, GL_LINK_STATUS, &programSuccess );
        if( programSuccess != GL_TRUE )
       {
               printf( "ERROR: linking program %d!\n", program );
		glDeleteProgram(program);
       
       }


}

void GPUcodes::EnableProgram(const std::string& name)
{
	for (int i=0; i<glprograms.size(); i++)
	{if(programnames[i] == name) glUseProgram(glprograms[i]); return ;}
	printf("ERROR : program not found\n");
}

void GPUcodes::EnableProgram(std::string&& name)
{
	EnableProgram(name);

}

void GPUcodes::EnableProgram(uint programindex)
{
	glUseProgram(glprograms[programindex]);

}

