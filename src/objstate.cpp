
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
* Default Constrctor except for setting window
* window needed just to get the time.
*
*/

StateEngine::StateEngine(Window_Class *window_):window(window_)
{
}

/*
* Update Vertex buffer of object to match the right frame of the state.
*
*/


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
