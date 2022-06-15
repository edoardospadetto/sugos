#include "./stateengine.h"

#include "../modules_/debugmisc_module.h"
#include "../context_/eventengine.h"
#include "../attributes_/state.h"
#include "../objects_/animatedobject2D.h"
/*
* Default Constrctor except for setting window
* window needed just to get the time.
*
*/

StateEngine::StateEngine(EventEngine *eventengine_): eventengine(eventengine_)
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
	//dbglog("miao ",x,y,currentState->w,currentState->h);
	int square[8] = {x,y+1,x+1,y+1,x+1,y,x,y};
	for (int i =0; i<4; i++)
	{
	 	animObj->vertex_buffer[4*i+2] = square[2*i]*currentState->w;
	 	animObj->vertex_buffer[4*i+3] = 1.0-square[2*i+1]*currentState->h;
	}
}

/*
*  Check if the frame of the animation has to be update
*  returns wheter the animation has been restarted because reaching
*  the last frame.
*/


bool StateEngine::CheckFrameUpdate()
{	

	if (eventengine == nullptr) printf("Error, clock not binded global context");
	int timeNow = eventengine->GetTime();
	if(lkeypress) 
	{
		//std::cout << "info  "  << (eventengine->GetState(triggerkeycode)) << " \n";
		return (eventengine->GetState(triggerkeycode) == PRESSED ) ;
	}
	else 
	{
		return ( timeNow-frameInit > currentState->GetCurrentFrameDuration() );
	}
	//if (time_above_threshold)
	//{
	//this->NextFrame(wentTimeOut, timeNow);
	//}	
			

}


/*
*  Override time triggers of frame update with a keycode
*/


bool StateEngine::TriggerFrameChangeOnKeyPress(int keycode_)
{
	lkeypress = true;
	triggerkeycode = keycode_;
	eventengine->TrackButton(keycode_);
}

/*
*  Updates the frame to the subsequent.
*/

bool StateEngine::NextFrame() // TRUE if animation RESTARTED
{

	++currentState->currentFrame; 
	
	bool restartedAnimation = ( currentState->currentFrame >= currentState->frameNum );
	if(restartedAnimation)
	{
		currentState->currentFrame=0;	
	}
	int tmp= currentState->currentFrame;
	currentState->x=currentState->row[tmp]; 
	currentState->y=currentState->col[tmp]; 
	frameInit = eventengine->GetTime(); // in principle should be the one from above, but should be fine 
	
	return restartedAnimation;
}

/*
*  Change animation.
*  Input is the time trigger, if the animation ended it can proceed with another animation
*  if specified, buttons triggger have to be specified unsing the interface
*/

void StateEngine::ChangeState(bool &wentTimeOut)
{
	
	
	for (int i=0; i<currentState->edges.size() ; i++)
	{
		SDL_Scancode key  = currentState->edges[i];
		

		if (key == TIME_OUT )
		{
			if (wentTimeOut) currentState = currentState->subsequents[i];
					
		}
		else if(eventengine->keyboard[key] + int(currentState->direction[i]) == 1 )
		{
			//std::cout << window->kb[key] << "\n" ;
			currentState = currentState->subsequents[i];
		}
		
	}
	
	
}

void StateEngine::AddState(State *state_)
{
	statesNetwork.push_back(state_);
	if (statesNetwork.size() ==1)
	{
		state_->currentFrame=0;
		currentState=statesNetwork[0];
	}
}



