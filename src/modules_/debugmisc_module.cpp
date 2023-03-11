
#include "./debugmisc_module.h"


//GLM MATH
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//===============================================================
//COUNT NUMBER OF SUBSTRING IN STRING
int countsubstr(const std::string& s, const std::string& target )
{
 int occurrences = 0;
 int pos = 0; 


   while ((pos = s.find(target, pos )) != std::string::npos) {
	      ++ occurrences;
	      pos += target.length();
   }
	return occurrences;
}
//===============================================================



void printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}
		
		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a program\n", program );
	}
}

void SugosAssert(bool cnd, const std::string& error_string )
{
	if(!cnd)
	{ 
		std::cout << error_string << "\n" ;
		throw std::exception();	
	}
}

void printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;
		
		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
		
		//Allocate string
		char* infoLog = new char[ maxLength ];
		
		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			printf( "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf( "Name %d is not a shader\n", shader );
	}
}


#ifdef OPENGLES_MACRO
#define VERSION(NAME)  NAME ## _KHR 
#else 
#define VERSION(NAME)  NAME
#endif
char const* gl_error_string(GLenum const err) noexcept
{
  switch (err)
  {
    // opengl 2 errors (8)
    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case VERSION(GL_STACK_OVERFLOW) :
      return "GL_STACK_OVERFLOW";

    case VERSION(GL_STACK_UNDERFLOW) :
      return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";
#ifdef OPENGL
    case GL_TABLE_TOO_LARGE :
      return "GL_TABLE_TOO_LARGE";
#endif
    // opengl 3 errors (1)
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    // gles 2, 3 and gl 4 error are handled by the switch above
    default:
      return "Unknown Error";
      
  }
}


GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case VERSION(GL_STACK_OVERFLOW):       error = "STACK_OVERFLOW"; break;
            case VERSION(GL_STACK_UNDERFLOW):      error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        throw std::exception();
    }
     
    return errorCode;
}

/*
void glStringifyEnumType()
{

GL_FLOAT                                        
GL_FLOAT_VEC2                                    
GL_FLOAT_VEC3                                    
GL_FLOAT_VEC4                                    
GL_DOUBLE                                        
GL_DOUBLE_VEC2                                   
GL_DOUBLE_VEC3                                   
GL_DOUBLE_VEC4                                   
GL_INT                                           
GL_INT_VEC2                                      
GL_INT_VEC3                                      
GL_INT_VEC4                                      
GL_UNSIGNED_INT                                  
GL_UNSIGNED_INT_VEC2                             
GL_UNSIGNED_INT_VEC3                             
GL_UNSIGNED_INT_VEC4                             
GL_BOOL                                          
GL_BOOL_VEC2                                     
GL_BOOL_VEC3                                     
GL_BOOL_VEC4                                     
GL_FLOAT_MAT2                                    
GL_FLOAT_MAT3                                    
GL_FLOAT_MAT4                                    
GL_FLOAT_MAT2x3                                  
GL_FLOAT_MAT2x4                                  
GL_FLOAT_MAT3x2                                  
GL_FLOAT_MAT3x4                                  
GL_FLOAT_MAT4x2                                  
GL_FLOAT_MAT4x3                                  
GL_DOUBLE_MAT2                                   
GL_DOUBLE_MAT3                                   
GL_DOUBLE_MAT4                                   
GL_DOUBLE_MAT2x3                                 
GL_DOUBLE_MAT2x4                                 
GL_DOUBLE_MAT3x2                                 
GL_DOUBLE_MAT3x4                                 
GL_DOUBLE_MAT4x2                                 
GL_DOUBLE_MAT4x3                                 
GL_SAMPLER_1D                                    
GL_SAMPLER_2D                                    
GL_SAMPLER_3D                                    
GL_SAMPLER_CUBE                                  
GL_SAMPLER_1D_SHADOW                             
GL_SAMPLER_2D_SHADOW                             
GL_SAMPLER_1D_ARRAY                              
GL_SAMPLER_2D_ARRAY                              
GL_SAMPLER_1D_ARRAY_SHADOW                       
GL_SAMPLER_2D_ARRAY_SHADOW                       
GL_SAMPLER_2D_MULTISAMPLE                        
GL_SAMPLER_2D_MULTISAMPLE_ARRAY                  
GL_SAMPLER_CUBE_SHADOW                           
GL_SAMPLER_BUFFER                                
GL_SAMPLER_2D_RECT                               
GL_SAMPLER_2D_RECT_SHADOW                        
GL_INT_SAMPLER_1D                                
GL_INT_SAMPLER_2D                                
GL_INT_SAMPLER_3D                                
GL_INT_SAMPLER_CUBE                              
GL_INT_SAMPLER_1D_ARRAY                          
GL_INT_SAMPLER_2D_ARRAY                          
GL_INT_SAMPLER_2D_MULTISAMPLE                    
GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY              
GL_INT_SAMPLER_BUFFER                            
GL_INT_SAMPLER_2D_RECT                           
GL_UNSIGNED_INT_SAMPLER_1D                       
GL_UNSIGNED_INT_SAMPLER_2D                       
GL_UNSIGNED_INT_SAMPLER_3D                       
GL_UNSIGNED_INT_SAMPLER_CUBE                     
GL_UNSIGNED_INT_SAMPLER_1D_ARRAY                 
GL_UNSIGNED_INT_SAMPLER_2D_ARRAY                 
GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE           
GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY     
GL_UNSIGNED_INT_SAMPLER_BUFFER                   
GL_UNSIGNED_INT_SAMPLER_2D_RECT                  
GL_IMAGE_1D                                      
GL_IMAGE_2D                                      
GL_IMAGE_3D                                      
GL_IMAGE_2D_RECT                                 
GL_IMAGE_CUBE                                    
GL_IMAGE_BUFFER                                  
GL_IMAGE_1D_ARRAY                                
GL_IMAGE_2D_ARRAY                                
GL_IMAGE_2D_MULTISAMPLE                          
GL_IMAGE_2D_MULTISAMPLE_ARRAY                    
GL_INT_IMAGE_1D                                  
GL_INT_IMAGE_2D                                  
GL_INT_IMAGE_3D                                  
GL_INT_IMAGE_2D_RECT                             
GL_INT_IMAGE_CUBE                                
GL_INT_IMAGE_BUFFER                              
GL_INT_IMAGE_1D_ARRAY                            
GL_INT_IMAGE_2D_ARRAY                            
GL_INT_IMAGE_2D_MULTISAMPLE                      
GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY                
GL_UNSIGNED_INT_IMAGE_1D                         
GL_UNSIGNED_INT_IMAGE_2D                         
GL_UNSIGNED_INT_IMAGE_3D                         
GL_UNSIGNED_INT_IMAGE_2D_RECT                    
GL_UNSIGNED_INT_IMAGE_CUBE                       
GL_UNSIGNED_INT_IMAGE_BUFFER                     
GL_UNSIGNED_INT_IMAGE_1D_ARRAY                   
GL_UNSIGNED_INT_IMAGE_2D_ARRAY                   
GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE             
GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY	     
GL_UNSIGNED_INT_ATOMIC_COUNTER                             
}
*/




