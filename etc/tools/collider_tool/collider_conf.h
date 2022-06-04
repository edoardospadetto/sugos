class ColliderConf
{
	public:
	int ii =0;
	GPUcodes *vrend;
	bool lpress=false;
	std::vector<VectorizedObject*> Polylines;
	Window_Class *w;
	Scene* s;
	float xold=0, yold=0;
	void EditCollider(MouseButton  press, float x_, float y_);
	ColliderConf(Window_Class *w_,Scene* s_); 
	void AddPoint(float x_, float y_);
	void Close();
	  //OBJECTS
	 




};

ColliderConf::ColliderConf(Window_Class *w_,Scene* s_): w(w_),s(s_)
{

	  vrend= new GPUcodes(w,"./src/shaders_/vectorizedobjectnc.shader");	
  	  vrend->Load("vecv","vecf", "vv");
  	
}

void ColliderConf::AddPoint(float x_, float y_)
{
	//Polylines->lmodib=true;
	//Polylines->lmodvb=true;
	/*
	int sizeibo = sizeof(Polylines->index_buffer)/sizeof(int);
	add_to_array(Polylines->vertex_buffer, x_);
	add_to_array(Polylines->vertex_buffer, y_);
	*/
	
	
	
	if(ii==0) 
	{
		xold = x_;
		yold=y_;
		ii=1;
	}
	else 
	{
	
		Polylines.push_back(new VectorizedObject(2,2,1,2,GL_LINES));
  	  	
		Polylines[Polylines.size()-1]->SpecifyBuffersAttributes("r_", 2);
		Polylines[Polylines.size()-1]->vertex_buffer[0]=xold;
		Polylines[Polylines.size()-1]->vertex_buffer[1]=yold;
		Polylines[Polylines.size()-1]->vertex_buffer[2]=x_;
		Polylines[Polylines.size()-1]->vertex_buffer[3]=y_;
		Polylines[Polylines.size()-1]->index_buffer[0]=0;
		Polylines[Polylines.size()-1]->index_buffer[1]=1;
		s->LoadObj( *(Polylines[Polylines.size()-1]), vrend->glprograms[0]);
		std::cout << xold << " " << yold << " " << x_ << " " << y_ << "\n";
		xold = x_;
		yold=y_;
	}
}


void ColliderConf::Close()
{
	/*int sizeibo = sizeof(Polylines->index_buffer)/sizeof(int);
	add_to_array(Polylines->index_buffer, Polylines->index_buffer[sizeibo]);
	add_to_array(Polylines->index_buffer, Polylines->index_buffer[0]+1);*/
	
}
void ColliderConf::EditCollider(MouseButton  press, float x_, float y_)
{
	

	
	if(!lpress && press ==1) 
	{
		lpress=true;
		AddPoint(x_, y_);
		std::cout << "in\n";
	}
	else if (press == 0) 
	{
		lpress=false;
	}
	
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );

	
			

}

