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
	ColliderConf(Window_Class *w_,Scene* s_, std::string name_, int Ncoll); 
	void AddInitialPoint(float x_, float y_);
	void AddFinalPoint(float x_, float y_, bool click);
	void Close();
	void AddCollider();
	void SetCollider(int num_, bool unload_);
	void MoveCollider(int i, bool unsafe_);
	
	void EmptyCurrentCollider();
	void LoadConfFile();
	void SaveCoords();
	  //OBJECTS
	 




};



void ColliderConf::LoadConfFile()
{
    std::string filepath_ = "./etc/tools/collider_tool/colliders/"+collidername+".xy";
	std::ifstream file;
	this->EmptyCurrentCollider();
	Polylines.clear();
	closed.clear();

	
	file.open(filepath_);
	
	if(file.is_open())
	{
		int Ncolliders; 
		file >> Ncolliders;
		for (int i=0; i<Ncolliders; i++)
		{
		    Polylines.push_back({});
	        closed.push_back(true);
			int Nvert;
			file >> Nvert;
			float vx, vy;
			
			for(int j=0; j<Nvert; j++)
			{
			
			    Polylines[i].push_back(new VectorizedObject(2,2,1,2,GL_LINES));
			    Polylines[i][j]->SpecifyBuffersAttributes("r_", 2);
                Polylines[i][j]->LinkUniformToVariable("CM", 4, GL_FLOAT);
                Polylines[i][j]->index_buffer[0]=0;
	            Polylines[i][j]->index_buffer[1]=1;
				
				file >> vx >> vy;
				if(j>0) 
				{
			        Polylines[i][j]->vertex_buffer[0]=Polylines[i][j-1]->vertex_buffer[2];
			        Polylines[i][j]->vertex_buffer[1]=Polylines[i][j-1]->vertex_buffer[3];
			    }
			    
			    Polylines[i][j]->vertex_buffer[2]=vx;
			    Polylines[i][j]->vertex_buffer[3]=vy;
			
			}
			Polylines[i][0]->vertex_buffer[0]=Polylines[i][Nvert-1]->vertex_buffer[2];
		    Polylines[i][0]->vertex_buffer[1]=Polylines[i][Nvert-1]->vertex_buffer[3];
		}
		
	}
	this->SetCollider(num,false);

}

ColliderConf::ColliderConf(Window_Class *w_,Scene* s_, std::string name_, int Ncolliders_): w(w_),s(s_), collidername(name_)
{

	  vrend= new GPUcodes(w,"./src/shaders_/vectorizedobjectnc.shader");	
  	  vrend->Load("vecv","vecf", "vv");
  	  for (int i=0; i< Ncolliders_; i++) this->AddCollider();
  	
}

void ColliderConf::AddInitialPoint(float x_, float y_)
{
	
	Polylines[num].push_back(new VectorizedObject(2,2,1,2,GL_LINES));

	Polylines[num][Polylines[num].size()-1]->SpecifyBuffersAttributes("r_", 2);
    Polylines[num][Polylines[num].size()-1]->LinkUniformToVariable("CM", 4, GL_FLOAT);
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[0]=x_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[1]=y_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[2]=x_;
	Polylines[num][Polylines[num].size()-1]->vertex_buffer[3]=y_;
	Polylines[num][Polylines[num].size()-1]->index_buffer[0]=0;
	Polylines[num][Polylines[num].size()-1]->index_buffer[1]=1;
	std::cout << (Polylines[num][Polylines[num].size()-1]) << "\n";
	s->LoadObject( Polylines[num][Polylines[num].size()-1], vrend->glprograms[0]);
	
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

void ColliderConf::EmptyCurrentCollider()
{
	for (int i=0; i<Polylines[num].size(); i++) 
	{
	
		s->UnloadObject( *(Polylines[num][i]));
		delete Polylines[num][i];
		
	}
	this->Polylines[num].clear();
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
			std::cout <<num <<" New\n";
			}
			lpress=true;
			
		}
		else if (press == 0) 
		{
			lpress=false;
		}
	}
	else 
	{
		if(!lpress && press ==1) 
		{
			closed[num]=false;
			this->EmptyCurrentCollider();
			lpress=true;
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

void ColliderConf::SetCollider(int num_, bool unload_)
{
	 if(unload_)
	 {
	 for (int i=0; i<Polylines[num].size(); i++)
	 {
		s->UnloadObject(*(Polylines[num][i]));
	 }
	 }
	 
	 if (!closed[num])
	 {
	    std::cout << "not closed\n";
	 	for (int i =0; i<  Polylines[num].size(); i++)
	 	{
	 		delete Polylines[num][i];
	 		Polylines[num].erase(Polylines[num].begin()+i);
	 	}
	 }
	 
	 num = num_;
	 for (int i=0; i<Polylines[num].size(); i++)
	 {
		s->LoadObject( Polylines[num][i] , vrend->glprograms[0] );
	 }
}


void ColliderConf::MoveCollider(int i, bool unsafe_)
{
	if(num+i == Polylines.size() && unsafe_) this->AddCollider();
	else if (num+i <0 | num+i > Polylines.size() ) throw std::exception();
	this->SetCollider(num+i, true);
}



