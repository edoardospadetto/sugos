class ColliderConf
{
	public:
	int ii =0;
	int num =0;
	GPUcodes *vrend;
	bool lpress=false;
	std::vector<bool> closed;
	std::vector<std::vector<VectorizedObject*>> Polylines;
	Window_Class *w;
	Scene* s;
	std::string collidername="";
	float xold=0, yold=0;
	void EditCollider(MouseButton  press, float x_, float y_);
	ColliderConf(Window_Class *w_,Scene* s_, std::string name_); 
	void AddInitialPoint(float x_, float y_);
	void AddFinalPoint(float x_, float y_, bool click);
	void Close();
	void AddCollider();
	void SetCollider(int num_);
	void MoveCollider(int i);
	
	void SaveCoords();
	  //OBJECTS
	 




};

ColliderConf::ColliderConf(Window_Class *w_,Scene* s_, std::string name_): w(w_),s(s_), collidername(name_)
{

	  vrend= new GPUcodes(w,"./src/shaders_/vectorizedobjectnc.shader");	
  	  vrend->Load("vecv","vecf", "vv");
  	
}

void ColliderConf::AddInitialPoint(float x_, float y_)
{
	
	Polylines[num].push_back(new VectorizedObject(2,2,1,2,GL_LINES));

	Polylines[num][Polylines[num].size()-1]->SpecifyBuffersAttributes("r_", 2);

	Polylines[num][Polylines[num].size()-1]->vertex_buffer[0]=x_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[1]=y_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[2]=x_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[3]=y_;
	Polylines[num][Polylines[num].size()-1]->index_buffer[0]=0;
	Polylines[num][Polylines[num].size()-1]->index_buffer[1]=1;
	std::cout << (Polylines[num][Polylines[num].size()-1]) << "\n";
	s->LoadObj( *(Polylines[num][Polylines[num].size()-1]), vrend->glprograms[0]);
	
}

void ColliderConf::AddFinalPoint(float x_, float y_, bool click)
{
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[2]=x_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[3]=y_;
	
	if(click) this->AddInitialPoint(x_,y_);
}



void ColliderConf::Close()
{
	if ( Polylines[num].size() > 0 ) 
	{
		AddFinalPoint(Polylines[num][0]->vertex_buffer[0], Polylines[num][0]->vertex_buffer[1], false);
	}
	closed[num] = true;
}
void ColliderConf::EditCollider(MouseButton  press, float x_, float y_)
{

	if (!closed[num])
	{
		if (Polylines[num].size()>0)
		{
			
			AddFinalPoint( x_, y_, false);
		} 
		
		if(!lpress && press ==1) 
		{
			if (Polylines[num].size()>0) AddFinalPoint( x_, y_, true);
			else {
			AddInitialPoint( x_, y_);
			std::cout <<num <<"New\n";
			}
			lpress=true;
			
		}
		else if (press == 0) 
		{
			lpress=false;
		}
	}
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );

}

void ColliderConf::SaveCoords()
{

	std::ofstream myfile ("./etc/tools/collider_tool/colliders/"+collidername+".xy");
	if (myfile.is_open())
	{
	    myfile << Polylines.size()<< "\n";
	    for (int i=0; i<Polylines.size(); i++)
	    {
	    myfile << Polylines[i].size()<< "\n";
	    for (int j=0; j<Polylines[i].size(); j++)
	    {
	     	myfile << Polylines[i][j]->vertex_buffer[0]<< " " <<  Polylines[i][j]->vertex_buffer[1] <<"\n";
	    }	
	    }
	    myfile.close();
	}
	else std::cout << "Unable to open file";
	
}


void ColliderConf::AddCollider()
{
	Polylines.push_back({});
	closed.push_back(false);
}

void ColliderConf::SetCollider(int num_)
{
	
	 for (int i=0; i<Polylines[num].size(); i++)
	 {
		s->UnloadObject(*(Polylines[num][i]));
	 }
	 
	 if (!closed[num])
	 {
	 	for (int i =0; i<  Polylines[num].size(); i++)
	 	{
	 		delete Polylines[num][i];
	 		Polylines[num].erase(Polylines[num].begin()+i);
	 	}
	 }
	 
	 num = num_;
	 for (int i=0; i<Polylines[num].size(); i++)
	 {
		s->LoadObj(*( Polylines[num][i]) , vrend->glprograms[0] );
	 }
}


void ColliderConf::MoveCollider(int i)
{
	if(num+i == Polylines.size()) this->AddCollider();
	else if (num+i <0 | num+i > Polylines.size() ) throw std::exception();
	this->SetCollider(num+i);
}
