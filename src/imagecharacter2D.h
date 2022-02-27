class ImageCharacter2D:: public VectorizedObject
{
	public:
	ImageCharacter2D():VectorizedObject(4,4,1,2,4); 		



}:

ImageCharacter2D::ImageCharacter2D(float width_, float height_):VectorizedObject(4,4,1,2,4)
{
	this->vertexbuffer  = new float[4*4] // 4 vertex x y t1 t2
	
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
	}
	
	for (int i =0; i<4; i++)
	{
		obj.index_buffer[i] = i;
	}
	
	//SCALE
	for (int i =0; i<4; i++)
	{	
		obj.vertex_buffer[4*i] *= width_*0.5;
		obj.vertex_buffer[4*i+1] *= height_*0.5;
		
	}
	 


}

