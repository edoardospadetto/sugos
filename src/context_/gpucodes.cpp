#include "./gpucodes.h" 
#include "../context_/window.h"
#include "../modules_/debugmisc_module.h"
#include "../enums.h"
#include <fstream>
#include <cstdio>
#include <algorithm>

//#include "../include/safe_include_SDLGL_OpenGL.h"

void GPUcodes::PrintSummary()
{
    dbglog(" ===================================== ");
	dbglog(" =======      SHADER SUMMARY    ====== ");
	dbglog(" ===================================== ");
	for(int i=0; i<shaders_type.size(); i++ )
	{
	    dbglog(" ",i, " | ", shaders_type[i], " | " , shaders_name[i] );
    }
}


void GPUcodes::ParseRaw(const std::string& path_)
{
	

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
	this->SplitRawInput(source);
	//printf(source);

}

GPUcodes::GPUcodes(Window_Class* parent_, std::string&& t): parent(parent_) {parent->MakeCurrent();ParseRaw(t);}//Compile();}
GPUcodes::GPUcodes(Window_Class* parent_, std::string& t): parent(parent_) {parent->MakeCurrent();ParseRaw(t);}//Compile();}
GPUcodes::GPUcodes(Window_Class* parent_, const std::string& t, std::string version_ ): parent(parent_) 
{	parent->MakeCurrent();
	this->SpecifyVersion(version_);
	ParseRaw(t);
	//Compile();
}


GPUcodes::GPUcodes(Window_Class* parent_): parent(parent_)
{}

void GPUcodes::AddSource(const std::string& path_)
{
    this->ParseRaw(path_);
}


void GPUcodes::SetParentWindow(Window_Class* parent_) {parent = parent_;} 

void GPUcodes::SpecifyVersion(std::string&& version_){SpecifyVersion(version_);}
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
			else if(type == "FUNCTION")
			{
			        shaders_type.push_back(GSLS_FUNCTION_VEC4IO);
			}
			else
			{
					shaders_type.push_back(-1);
			}

			
			
			rawin = rawin.substr(pos2+1);
		
		}

		
}

int GPUcodes::CompileIdx(int idx)
{

	const char *shader_input = shaders[idx].c_str();
	GLint id=0;
	shaders_id.push_back(-1);
		
			
    int err = this->Compile(shader_input, shaders_type[idx], id);
    switch (err)
    {
        case 0 :
            shaders_id[shaders_id.size()-1] = id;
            dbglog(" SUCCESSFULL  ", shaders_name[idx], shaders_id[idx]);
            break;
        
        case -1:
            printf( "ERROR : Unable to compile Shader %d, type %s name %s \n", 
				idx, types[shaders_type[idx]].c_str(), shaders_name[idx].c_str() );
			throw std::exception();
            break; 
        
        case -2:
            printf("ERROR : Invalid Input for Shader %d, type %s name %s \n", 
		 	idx, types[shaders_type[idx]].c_str(), shaders_name[idx].c_str() );
		 	throw std::exception();
            break;
    }

    return shaders_id.size()-1;
}

int GPUcodes::Compile(const char* source, GLenum shaderType,  GLint& id )
{

    id = glCreateShader(shaderType);

	glShaderSource( id, 1 , &source , NULL);
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
			
			glGetShaderInfoLog( id, length, &length, info );
			printf("%s", info);
			delete[] info ;
			
			return -1;
			
		 }
		 else return -2;
		  
	}
	else return 0;

}


void GPUcodes::Load(std::string&& vertexname, std::string&& fragmentname, std::string&& programname  )
{

	Load(vertexname,fragmentname, programname);
}

int GPUcodes::FindNameIndex(const std::string& name)
{
    auto shader_pos = std::find(&(shaders_name[0]), &(shaders_name[0]) + shaders_name.size() , name);

	int idx = std::distance(&(shaders_name[0]),shader_pos);
	if(idx == shaders_name.size())
	{
		printf("ERROR: Shader, name |%s| not found. No shader in use.\n",name.c_str());
		throw std::exception();
	}
	
	return idx;

}

// Function doing a collare of strings, to add function add the end 
// of vertex shader
void GPUcodes::CombineFunction(std::string& body, int idx_f, int idx_temp )
{
    
    
    int delimiter0=body.find(" main(");
    int delimiter1=body.rfind("\n", delimiter0);
    int delimiter2=body.find("gl_Position");
    int delimiter3=body.find("=", delimiter2+1);
    int delimiter4=body.find('\n', delimiter3+1);

    std::string body0 = body.substr (0,delimiter1); 
    std::string body1 = body.substr (delimiter1,delimiter2-delimiter1); 
    std::string body2 = body.substr (delimiter3,delimiter4-delimiter3);

    std::string body3 = body.substr (delimiter2,delimiter3-delimiter2); // gl_position 
    std::string body4 = body.substr (delimiter4,body.length()-delimiter4); 	


    delimiter0=this->shaders[idx_f].find("{");
    delimiter1=this->shaders[idx_f].rfind("(", delimiter0);
    delimiter2=this->shaders[idx_f].rfind(" ", delimiter1); 
    while (this->shaders[idx_f][delimiter2+1] == ' ' |  this->shaders[idx_f][delimiter2+1] == ' ' )
    {
        delimiter1 = delimiter2;
        delimiter2=this->shaders[idx_f].rfind(" ", delimiter2);
    }
    std::string function_name = this->shaders[idx_f].substr(delimiter2+1, delimiter1-delimiter2-1);

    std::cout << "teest "<< delimiter0 << " "<< delimiter1 << " "<< delimiter2 << " "<< delimiter3 << " "<< delimiter4 << " " << "\n";

    if(shaders_type[idx_f] != GSLS_FUNCTION_VEC4IO) throw std::exception();


    body = body0 + this->shaders[idx_f] + body1 + "vec4 sugos_reserved_"+std::to_string(idx_temp) + body2+"\n   "+
       body3 + "="+ function_name + "("+ "sugos_reserved_"+std::to_string(idx_temp) +");"+body4 ;
        
	//std::cout << "-------------------------\n";
	//std::cout << body ; 
	//std::cout << "-------------------------\n";
	
}


void GPUcodes::Load(std::initializer_list<std::string>&& combinedVertex,std::initializer_list<std::string>&& combinedFragment, std::string&& programName  )
{
    this->Load(combinedVertex,combinedFragment,programName  );
}

void GPUcodes::Load(const std::initializer_list<std::string>& combinedVertex,const std::initializer_list<std::string>& combinedFragment, const std::string& programName  )
{
    


    int idx_v = this->FindNameIndex(*( combinedVertex.begin()  ) );
    int idx_f = this->FindNameIndex(*( combinedFragment.begin()) );
    

    
    if(shaders_type[idx_v] != GL_VERTEX_SHADER ) throw std::exception();
    if(shaders_type[idx_f] != GL_FRAGMENT_SHADER ) throw std::exception();
    

    
    std::string vertexBody = this->shaders[idx_v];
    std::string fragmentBody = this->shaders[idx_f];
    
   
    int idx_temp =0;
    for(auto it=combinedVertex.begin()+1; it!= combinedVertex.end(); it++) 
    {
        this->CombineFunction(vertexBody, this->FindNameIndex( *it ), idx_temp);
        ++idx_temp;
    }
    idx_temp =0;
    for(auto it=combinedFragment.begin()+1; it!= combinedFragment.end(); it++)
    {
         this->CombineFunction(fragmentBody,  this->FindNameIndex(*it ), idx_temp);
         ++idx_temp;
    }
    
    int id_v=0, id_f=0;
    this->Compile(vertexBody.c_str(), GL_VERTEX_SHADER, id_v );
    this->Compile(fragmentBody.c_str(), GL_FRAGMENT_SHADER, id_f );

    this->Link(id_v, id_f, programName);


}

void GPUcodes::Load(const std::string& vertexName, const std::string& fragmentName, const std::string& programName )
{

    dbglog("\n Load Shaders...");
	
	parent->MakeCurrent();

	int idx_a = this->FindNameIndex(vertexName);
	int idx_b = this->FindNameIndex(fragmentName);
    int idx_v = this->CompileIdx(idx_a);
    int idx_f = this->CompileIdx(idx_b);	
    
    dbglog("Compiling SUCCESSFULL  ", shaders_name[idx_a], shaders_id[idx_v]);
	dbglog("Compiling SUCCESSFULL  ", shaders_name[idx_a], shaders_id[idx_f]);
	
	this->Link(idx_v, idx_f, programName);
    

}

void GPUcodes::Link(int idV, int idF, const std::string& programName)
{

    GLuint program =  glCreateProgram();
	
    glAttachShader(program, idV);
	glAttachShader(program, idF);
	
	glprograms.push_back(program); 
	this->programnames.push_back(programName); 
	glLinkProgram(program);
	
	GLint programSuccess = GL_TRUE;
    glGetProgramiv( program, GL_LINK_STATUS, &programSuccess );
    
    if( programSuccess != GL_TRUE )
    {
        printf( "ERROR: linking program %d!\n", program );
        glDeleteProgram(program);
   
    }
    
    glDetachShader(program,idV);
    glDeleteShader(idV);
    glDetachShader(program,idF);
    glDeleteShader(idF);


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

// @to_do smart compiling of object, if already compiled keep in memory. 

