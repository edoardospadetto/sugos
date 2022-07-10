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
class VectorizedObject;

class Camera_2D
{
	private:
		float cx=0;
		float cy=0;
		float w=1;
		float h=1;
		std::string camera_gsls;
		std::string camera_uniform;
		
		float camera[16] = {0.0};
		
		std::vector<VectorizedObject*> binded_objects;
		std::vector<std::string> uniform_names;
		
		void ComputeMatrix();
		
	
	public:
		Camera_2D(float cx_,float cy_,float w_,float h_);
		void BindObject(VectorizedObject* object, const std::string& uniformName);
		void Move(float dx,float dy);
		void OpenView(float dw,float dh);
		void Update();
	
};

#endif
