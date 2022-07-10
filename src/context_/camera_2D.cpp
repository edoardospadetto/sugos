#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>

#include "../objects_/vectorizedobject.h"



#include "camera_2D.h"

Camera_2D::Camera_2D(float cx_, float cy_, float w_, float h_): cx(cx_), cy(cy_), w(w_), h(h_)
{
	std::ifstream buffer_gsls("./src/shaders_/2Dcamera_fun.gsls", std::ios_base::in);
	
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
		this->Update();
}

void Camera_2D::Move(float dx, float dy)
{
	cx+=dx;
	cy+=dy;
	
	
}


void Camera_2D::OpenView(float dw, float dh)
{
	w+=dw;
	h+=dh;
}


void Camera_2D::ComputeMatrix()
{
    camera[0]  = 1.0/w; 
	camera[5]  = 1.0/h; 
	camera[10] = 1.0;	
	camera[4]  = -cx;
	camera[8]  = -cy;
	camera[11] = 0.0;
	camera[15] = 1.0;
}

void Camera_2D::Update()
{
    for(int i=0; i<this->binded_objects.size() ; i++)
    {
        for(int j=0; j<16 ; j++)
        {
            this->binded_objects[i]->SetUniform(this->uniform_names[i],j,camera[j]) ; 
        }
    }

}
