/*     _
       \`*-.                    
        )  _`-.                 
       .  : `. .                
       : _   '  \               
       ; *` _.   `*-._          
       `-.-'          `-.       
         ;       `       `.     
         :.       .        \    
         . \  .   :   .-'   .   
         '  `+.;  ;  '      :   
         :  '  |    ;       ;-. 
         ; '   : :`-:     _.`* ;
[bug] .*' /  .*' ; .*`- +'  `*' 
      `*-*   `*-*  `*-*'     
*/

#ifndef CAMERA_2D
#define CAMERA_2D
                              
#include <vector>
#include <string>
#include "../include/safe_include_glm.h"
class VectorizedObject;

class Camera_2D
{
	private:
		
		std::string camera_shader_path = "./src/shaders/2Dcamera_fun.gsls";
		std::string camera_gsls;
		std::string camera_uniform;
		
		
		
		std::vector<VectorizedObject*> binded_objects;
		std::vector<std::string> uniform_names;
		
		void ComputeMatrix();
		
	
	public:
		Camera_2D(float cx_,float cy_,float w_,float h_);
		void BindObject(VectorizedObject* object, const std::string& uniformName);
		void Move(float dx,float dy);
		void OpenView(float dw,float dh);
		void SetPos(float x, float y);
		void Update();
		float cx=0;
		float cy=0;
		float w=1;
		float h=1;
		glm::mat4 camera = glm::mat4( 0.0 );
		glm::mat4 inversecamera = glm::mat4( 0.0 );
	
};

#endif
