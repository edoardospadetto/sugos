

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
		dbglog(i, obj.vertex_buffer[i]);
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
					 
}


void GenQuadText(VectorizedObject& obj)
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
		dbglog(i, obj.vertex_buffer[i]);
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
	
	//SCALE
	for (int i =0; i<4; i++)
	{	
		obj.vertex_buffer[4*i] *= 1;
		obj.vertex_buffer[4*i+1] *= 1;
		
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


void GenTriangle(VectorizedObject& obj)
{
	float vertex[]= 	//VBO data
	{	
		 0.05f,  0.0f,
		-0.05f,  -0.03f,
		-0.00f,  sqrt(3)*0.05f,

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




/*

void GenColor(float* target, float r ,float g, float b)
{
	size_t vertices = sizeof(target)/(3*sizeof(target[0]));
	
	for( int i =0; i< vertices, i++  )
	{
		target[3*i+0] = r;
		target[3*i+1] = g;
		target[3*i+2] = b; 
	}	
}

GenTriangleObj( VectorizedObject& obj, float x, float y, float z )
{

	
	for (int i =0; i<6; i++)
	{
		obj.vertex_buffer[i] = vertex[i];
	}
	
	for (int i =0; i<3; i++)
	{
		obj.index_buffer[i]=i;
	}	

}
*/


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


