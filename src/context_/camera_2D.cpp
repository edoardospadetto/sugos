#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>

#include "../include/glm/gtc/type_ptr.hpp"
#include "../objects_/vectorizedobject.h"



#include "camera_2D.h"

Camera_2D::Camera_2D(float cx_, float cy_, float w_, float h_): cx(cx_), cy(cy_), w(w_), h(h_)
{
	std::ifstream buffer_gsls(camera_shader_path, std::ios_base::in);
	std::cout << camera_shader_path << " \n";
	if(buffer_gsls.is_open())
	{
		std::stringstream buffer_string;
		buffer_string << buffer_gsls.rdbuf();;
		this->camera_gsls = buffer_string.str();
		
	}
	else
	{
		printf("Error: gsls camera not open\n");
		throw std::exception();
	}	
	
	this->ComputeMatrix();
	this->Update();
}


void Camera_2D::BindObject(VectorizedObject* object, const std::string& uniformName)
{
        this->binded_objects.push_back(object);
		this->uniform_names.push_back(uniformName);
		object->LinkUniformToVariable(uniformName, 16, GL_FLOAT);
		this->Update();
}

void Camera_2D::Move(float dx, float dy)
{
	cx+=dx;
	cy+=dy;
	
	
}

void Camera_2D::SetPos(float x, float y)
{
	cx=x;
	cy=y;
}




void Camera_2D::OpenView(float dw, float dh)
{
	w+=dw;
	h+=dh;
}


void Camera_2D::ComputeMatrix()
{
    camera[0][0]  = 1.0/w; 
    camera[1][1]  = 1.0/h;
    camera[2][2]  = 1.0;
    camera[3][3]  = 1.0;
    camera[3][0]  = -cx/w;
    camera[3][1]  = -cy/w;
    camera[3][2]  = 0.0;
	//camera[12]  = -cx;
	//camera[13]  = -cy;
	//camera[11] = 0.0;
	//camera[15] = 1.0;
}

/*
void Camera_2D::InvertMatrix()
{
    
    glm::mat4 bbb = glm::make_mat4(ca);

}
*/

void Camera_2D::Update()
{
    this->ComputeMatrix();
    for(int i=0; i<(int)(this->binded_objects.size()) ; i++)
    {
        for(int j=0; j<16 ; j++)
        {
            this->binded_objects[i]->SetUniform(this->uniform_names[i],j,camera[j/4][j%4]) ; 
            //std::cout << camera[j] << " " ; 
            //if(j % 4 == 3 ) std::cout << "\n"; 
        }
       // std::cout << "\n";
    }
    
    

}
