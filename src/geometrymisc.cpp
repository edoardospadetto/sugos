

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
		-1.0f, -1.0f, 0.0f,  0.0f,
		 1.0f, -1.0f, 1.0f,  0.0f,
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
		-0.05f,  0.0f,
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
