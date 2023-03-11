#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "../include/safe_include_SDLGL_OpenGL.h"
#include "../include/safe_include_glm.h"


#include "../enums.h"
#include "./debugmisc_module.h"
#include "../objects_/vectorizedobject.h"
#include "../attributes_/collider.h"
#include "../objects_/colliderobject2D.h"



// Generate Triangle 
// Size of vertex =2 just x and y
void GenTriangle(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{	
		 0.05f,  0.0f,
		-0.05f,  -0.03f,
		-0.00f,   static_cast<float>(sqrt(3))*0.05f,

	};

	
	
	for (int i =0; i<6; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<3; i++)
	{
		obj.index_buffer[i]=i;
	}
	

}

//Generate Square
// Size of vertex =2 just x and y
void GenQuad(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-0.05f, -0.05f,
		 0.05f, -0.05f,
		 0.05f,  0.05f,
		-0.05f,  0.05f
	};

	for (int i =0; i<8; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
					 
}

void GenColorQuad(VectorizedObject& obj, float xa,float ya,float x1,float y1)
{
	float vertex[]= 	//VBO data
	{
		xa, ya, 1.0,0.5,0.5,1.0,
		x1, ya, 1.0,0.5,0.5,1.0,
		x1, y1, 1.0,0.5,0.5,1.0,
		xa, y1, 1.0,0.5,0.5,1.0
	};

	for (int i =0; i<24; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
					 
}


void GenQuad2TColor(VectorizedObject& obj,float xa,float ya,float x1,float y1)
{
	float vertex[]= 	//VBO data
	{
		xa, ya, 1.0,0.5,0.5,1.0,
		x1, ya, 1.0,0.5,0.5,1.0,
		x1, y1, 1.0,0.5,0.5,1.0,
		xa, y1, 1.0,0.5,0.5,1.0
	};

	for (int i =0; i<24; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	
	obj.index_buffer[0] = 0;
	obj.index_buffer[1] = 1;
	obj.index_buffer[2] = 1;
	obj.index_buffer[3] = 2;
	obj.index_buffer[4] = 2;
	obj.index_buffer[5] = 3;
	obj.index_buffer[6] = 3;
	obj.index_buffer[7] = 0;
	
	
	
	
	for (int i =0; i<4; i++)
	{	
		obj.vertex_buffer[4*i] *= 1;
		obj.vertex_buffer[4*i+1] *= 1;
		
	}
					 
}

void GenQuad2TText(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-1.0f, -1.0f, 0.0f,  0.0f, // bottom left
		 1.0f, -1.0f, 1.0f,  0.0f, // bottom right
		 1.0f,  1.0f, 1.0f,  1.0f,
		-1.0f,  1.0f, 0.0f,  1.0f
	};

	for (int i =0; i<16; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	
	obj.index_buffer[0] = 0;
	obj.index_buffer[1] = 1;
	obj.index_buffer[2] = 2;
	obj.index_buffer[3] = 0;
	obj.index_buffer[4] = 2;
	obj.index_buffer[5] = 3;
	
	
	
	for (int i =0; i<4; i++)
	{	
		obj.vertex_buffer[4*i] *= 1;
		obj.vertex_buffer[4*i+1] *= 1;
		
	}
					 
}


void GenQuad2T(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-1.0f, -1.0f, // bottom left
		 1.0f, -1.0f, // bottom right
		 1.0f,  1.0f,
		-1.0f,  1.0f
	};

	for (int i =0; i<8; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	
	obj.index_buffer[0] = 0;
	obj.index_buffer[1] = 1;
	obj.index_buffer[2] = 2;
	obj.index_buffer[3] = 0;
	obj.index_buffer[4] = 2;
	obj.index_buffer[5] = 3;
					 
}


// Generate a square with texture
void GenQuadText(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-1.0f, -1.0f, 0.25f, 0.25f, // bottom left
		 1.0f, -1.0f, 0.4f, 0.25f, // bottom right
		 1.0f,  1.0f, 0.4f, 0.4f,
		-1.0f,  1.0f, 0.25f, 0.4f
	};

	for (int i =0; i<16; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
	
	
	for (int i =0; i<4; i++)
	{	
		obj.vertex_buffer[4*i] *= 1;
		obj.vertex_buffer[4*i+1] *= 1;
		
	}
					 
}



// Generate Colored Polygon
void GenColoredPolygon(VectorizedObject *obj, int sides_, float radius_, float r,float g,float b, float a)
{

	 
	float angle = 2*M_PI/float(sides_);
	
	obj->vertex_buffer[0] = 0.0;
	obj->vertex_buffer[1] = 0.0; 
	obj->vertex_buffer[2] = r;
	obj->vertex_buffer[3] = g;
	obj->vertex_buffer[4] = b;
	obj->vertex_buffer[5] = a;
	
	for (int i =1; i<sides_+1; i++)
	{
		obj->vertex_buffer[6*i+0] = radius_*cos((i-1)*angle);
		obj->vertex_buffer[6*i+1] = radius_*sin((i-1)*angle); 
		obj->vertex_buffer[6*i+2] = r;
		obj->vertex_buffer[6*i+3] = g;
		obj->vertex_buffer[6*i+4] = b;
		obj->vertex_buffer[6*i+5] = a;
		
	}
	
	for (int i =0; i<sides_; i++)
	{
		obj->index_buffer[3*i+0]=i+1;
		obj->index_buffer[3*i+1]=0;
		obj->index_buffer[3*i+2]=i+2;
	
	}	
	obj->index_buffer[3*(sides_-1)+0]=sides_;
	obj->index_buffer[3*(sides_-1)+2]=1;
		
	
}


void SetColor(VectorizedObject *obj,int sides_, float r,float g,float b, float a)
{

	for (int i =0; i<sides_+1; i++)
	{
		
		obj->vertex_buffer[6*i+2] = r;
		obj->vertex_buffer[6*i+3] = g;
		obj->vertex_buffer[6*i+4] = b;
		obj->vertex_buffer[6*i+5] = a;
		
	}	
}


// Generate Polygon

void GenPolygon(VectorizedObject *obj, int sides_, float radius_)
{

	 
	float angle = 2*M_PI/float(sides_);
	
	obj->vertex_buffer[0] = 0.0;
	obj->vertex_buffer[1] = 0.0; 
	
	
	for (int i =1; i<sides_+1; i++)
	{
		obj->vertex_buffer[2*i+0] = radius_*cos((i-1)*angle);
		obj->vertex_buffer[2*i+1] = radius_*sin((i-1)*angle); 
		
	
	}	
	
	for (int i =0; i<sides_; i++)
	{
		obj->index_buffer[3*i+0]=i+1;
		obj->index_buffer[3*i+1]=0;
		obj->index_buffer[3*i+2]=i+2;
	
	}	
	obj->index_buffer[3*(sides_-1)+0]=sides_;
	obj->index_buffer[3*(sides_-1)+2]=1;
	
	
}


// Given obj as above 
// colored or not, give back its collider 
// It has to be initialized with 
// void GenPolygon or void GenColoredPolygon

void GenPolygonCollider(ColliderObject2D *obj, int sides_, bool colored)
{
	int stride = 2;
	//int sides = sizeof(obj->vertex_buffer) / (sizeof(obj->vertex_buffer[0])*stride);
	
	//dbglog("sides , ", sides, sizeof(obj->vertex_buffer),sizeof(obj->vertex_buffer[0] ));
	std::vector<glm::vec2> x;
	if ( colored )  stride=6;
	
	for (int i =1; i<  sides_+1; i++)
	{ 	
            x.push_back( glm::vec2 ( obj->vertex_buffer[stride*i+0] , 
				       obj->vertex_buffer[stride*i+1] ) ) ;
	}	
	
	obj-> collider = new Collider2D(std::move(x), GENERIC);
}







// Attach together 2 arrays, 
// Ax1 Ay1 Ax2 Ay2 Ax3 Ay3 this has stride 2
// Bx1 By1 Bz1 Bx2 By2 Bz1 Bx3 By3 Bz3 this has stride 3
// become
// Ax1 Ay1 Bx1 By1 Bz1 Ax2 Ay2 Bx2 By2 Ax3 Ay3 Bz1 Bx3 By3 Bz3


template<typename T>
void JoinBufferInstances(T* a_, int stridea_,  T* b_, int strideb_, T* c)
{
	
	size_t bytes = sizeof(a_[0]);
	size_t sizea = sizeof(a_)/bytes;
	size_t sizeb = sizeof(b_)/bytes;
	size_t stride = stridea_+ strideb_;
	size_t vertexnum = sizea/stridea_;
	
	
	if(sizea%stridea_ && sizeb%strideb_  )
	{
		printf("[ %s : %s ] Error, instance vertex is not a multiple of the whole instance array.", __FILE__, __LINE__  );
		
	}
	if(sizea/stridea_ != sizeb/stridea_  )
	{
		printf("[ %s : %s ] Error, instance array of different sizes.", __FILE__, __LINE__  );
		
	}
	
	if ( sizeof(c)/bytes != vertexnum*stride  )
	{
		printf("[ %s : %s ] Error, output array allocated with wrong size.", __FILE__, __LINE__  );
	}
	
	for (int i=0; i<vertexnum; i++)
	{
		memcpy( c[i*stride], a_[i*stridea_], bytes*stridea_ );
		memcpy( c[i*stride + stridea_], b_[i*strideb_], bytes*stridea_ );
	}
    	
	
}




/*
void GenProj(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		-0.01f, -0.01f,
		 0.01f, -0.01f,
		 0.01f,  0.01f,
		-0.01f,  0.01f
	};

	
	
	for (int i =0; i<8; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
		dbglog(i, obj.vertex_buffer[i]);
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
	
						 
}



void GenColor(float* target, float r ,float g, float b)
{
	size_t vertices = sizeof(target)/(3*sizeof(target[0]));
	
	for( int i =0; i< vertices; i++  )
	{
		target[3*i+0] = r;
		target[3*i+1] = g;
		target[3*i+2] = b; 
	}	
}


void GenTriText(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{
		 0.05f, -0.3f, 1.0f, 1.0f,
		-0.05f, -0.3f, 1.0f, 1.0f,
		 0.00f, sqrt(3)*0.05f, 0.3f, 0.3f

	};
	
	for (int i =0; i<12; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
		dbglog(i, obj.vertex_buffer[i]);
	}
	
	for (int i =0; i<3; i++)
	{
		obj.index_buffer[i] = i;
	}
					 
}
*/

