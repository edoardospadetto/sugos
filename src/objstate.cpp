

//Set subsequent state to
//if -1 is on time out  


void State::ConnectTo(State* p_stat, SDL_Scancode key, Direction whichdirection)
{
	
	subsequents.push_back(p_stat);
	edges.push_back(key);
	direction.push_back(whichdirection);
}



/*
* Set animation snapshot size in width and height. The measure is pixel.
* Texture file mush have snapshots with the same size ^^
*/ 



/*State::State (int row_,int col_,int w_,int h_,unsigned int duration_,GLuint textureId_):
row(row_), col(col_), w(w_), h(h_), duration(duration_), textureId(textureId_)
{
	row.push_back()
}*/
/*
State::State(std::string&& confFile_)
{
	State(confFile_);	
}
*/

//Configure animation from an already defined texture and conf file.
State::State(const std::string& confFile, Texture* texture_)
{

	int load_NameDataInfo[2]={-1,-1}; // 1) MOD, 2) MEM // mods { name = 0, data=1, infor=2, idle = -1}
	
	std::string line;
	std::ifstream fileBuffer;
	fileBuffer.open(confFile);
	dbglog("==================================");
	dbglog("Open Anim : ", confFile);
	dbglog("==================================");
	dbglog("");
	if ( fileBuffer.is_open() ) {
		while ( fileBuffer ) {
			std::getline (fileBuffer, line);
			//dbglog(line);
			int lim_a = 0, lim_b=0;
			std::string token;
			while(lim_b>=0)
			{	
				
				lim_b = line.find(" ",lim_a);
				//dbglog("             ", lim_a,lim_b);
				//if(lim_b < 0 ) lim_b=line.length()-1;
				token=line.substr(lim_a,lim_b-lim_a);
				if(token!=" " && token!="" )
				{ 
					//token=line.substr(lim_a,lim_b-lim_a);
					//dbglog(token);   
					//Rules
					if( token=="~anim") {load_NameDataInfo[0]=0;load_NameDataInfo[1]=0;}
					else if( token=="~data") {load_NameDataInfo[0]=1;load_NameDataInfo[1]=0;}
					else if( token=="~info") {load_NameDataInfo[0]=2;load_NameDataInfo[1]=0;}
					else ++load_NameDataInfo[1];
					this->Parser( token, load_NameDataInfo);
						
				}
		
				lim_a=lim_b+1;
				
			
				
				
			}
		}

	}
	else
	{
		printf("Error, file: %s not found", confFile.c_str());
	}
	
	
	stateTexture=texture_;
	
	if(frameNum%4 !=0 )
	{
		printf("Error, ill config file");
		throw std::exception();
	}
	frameNum = frameNum/4;
	x=row[0];
	y=col[0];
	SetFrameSizePx(wpx, hpx);
	dbglog("sizes", w, h);
		
	
	dbglog("        ----------------");
	dbglog("       | **  Loaded **  |");
	dbglog("        ----------------");
}

void State::Parser(const std::string& token_, int namedatainfo_[])
{
	dbglog(token_, namedatainfo_[0], namedatainfo_[1] );
	if(namedatainfo_[1] !=0 ) // do not care section title, avoid issue %3 later
	{
		switch( namedatainfo_[0])
		{
			case 0 : // ~anim
				if(namedatainfo_[1] == 1) this->name=token_;
				break;
			case 1 : // ~data
				switch((namedatainfo_[1]-1)%4) 
				{
					case 0:
						++frameNum;
						break;
					case 1:
						++frameNum;
						row.push_back(stoi(token_));
						break;
					case 2:
						++frameNum;
						col.push_back(stoi(token_));
						break;
					case 3:
						++frameNum;
						duration.push_back(stoi(token_));
						break;
				 
				}
				//dbglog("frameNum", frameNum, (namedatainfo_[1]-1)%4, token_);
				break;
				
			
			case 2 : // ~data
				switch(namedatainfo_[1])
				{
					case 1: // file path
						imgPath = token_;
						break;
					case 2: // width
						wpx = stoi(token_);
						break;
					case 3: //height
						hpx = stoi(token_);
						break;
				 
				}
				break;
		
		}
	}
}



/*
Set animation snapshot size in width and height. The measure is pixel.
*/ 
void State::SetFrameSizePx(int sizex_, int sizey_)
{
	
	if(sizex_ < 0.0 | sizex_ >  stateTexture->tx_width | sizey_ < 0.0 | sizey_ > stateTexture->tx_height) 
	{
		printf("Error : OpenGL Texture sizes ranges from 0 to %d for width, and 0 to %d for height \n \n ", stateTexture->tx_width, stateTexture->tx_height);
	}
	dbglog("-", sizex_,sizey_,stateTexture->tx_width,stateTexture->tx_height );
	w = float(sizex_)/stateTexture->tx_width;
	h = float(sizey_)/stateTexture->tx_height;
	
	int snapshotnumx = stateTexture->tx_width/sizex_;
	int snapshotnumy = stateTexture->tx_width/sizex_;
	
	dbglog( "Snapshot num x,y: ",snapshotnumx,snapshotnumy, " outbound: " , stateTexture->tx_width%sizex_, stateTexture->tx_height%sizey_  );
	if ( stateTexture->tx_width%sizex_ | stateTexture->tx_height%sizey_ ) printf("Error, non integer number of snapshots check snapshot size or texture size.");

}


void State::SetFrameSize(float sizex_, float sizey_)
{	
	if(sizex_ < 0.0 | sizex_ > 1.0 | sizey_ < 0.0 | sizey_ > 1.0) printf("Error : OpenGL Texture sizes ranges from 0.0 to 1.0 \n \n");
	w  = sizex_;
	h  = sizey_;
}


unsigned int State::GetCurrentFrameDuration() {return duration[currentFrame]; }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
* Update Vertex buffer of object to match the right frame of the state.
*
*
*/

StateEngine::StateEngine(Window_Class *window_):window(window_)
{

}

void StateEngine::UpdateVBatFrame(AnimatedObject2D* animObj) //count from 0 
{	
	int x = currentState->x;
	int y = currentState->y;
	dbglog(x,y,currentState->w,currentState->h);
	int square[8] = {x,y+1,x+1,y+1,x+1,y,x,y};
	for (int i =0; i<4; i++)
	{
	 	animObj->vertex_buffer[4*i+2] = square[2*i]*currentState->w;
	 	animObj->vertex_buffer[4*i+3] = 1.0-square[2*i+1]*currentState->h;
	}
}

void StateEngine::AnimateState(bool &wentTimeOut)
{	

	if (window == nullptr) printf("Error, clock not binded global context");
	int timeNow = window->GetTime();
	
	if (timeNow-frameInit > currentState->GetCurrentFrameDuration())
	{
		++currentState->currentFrame; 
	
		wentTimeOut = ( currentState->currentFrame >= currentState->frameNum );
		if(wentTimeOut)
		{
			currentState->currentFrame=0;
			
		}
		int tmp= currentState->currentFrame;
		currentState->x=currentState->row[tmp]; 
		currentState->y=currentState->col[tmp]; 
		frameInit = timeNow;
	}	
			

}

void StateEngine::AddState(State *state_)
{
	statesNetwork.push_back(state_);
	if (statesNetwork.size() ==1)
	{
		currentState=statesNetwork[0];
	}
}


void StateEngine::ChangeState(bool &wentTimeOut)
{
	
	
	for (int i=0; i<currentState->edges.size() ; i++)
	{
		SDL_Scancode key  = currentState->edges[i];
		
		if (key == TIME_OUT )
		{
			if (wentTimeOut) currentState = currentState->subsequents[i];
					
		}
		else if(window->kb[key] + int(currentState->direction[i]) == 1 )
		{
			currentState = currentState->subsequents[i];
		}
		
	}
	
	
}
