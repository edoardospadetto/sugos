
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



#ifndef STATEENGINE
#define STATEENGINE

// Animation related classes and code

/* 
*
* Engine to hangle animations of a single object.
* One state many frame, engine knows all the state for an object
* 
* Thought to be symbiotic with AnimObj
*
*/
#include <vector>
#include <SDL2/SDL.h>
class State;
class EventEngine;
class AnimatedObject2D;

class StateEngine
{	
	private:
	
		unsigned int frameInit;
		bool lkeypress=false;
		int triggerkeycode;
	
	public:
	
		SDL_Scancode animGen;
		EventEngine *eventengine=nullptr;
		//Window_Class *window=nullptr;
		unsigned int* clock;
		int* State_duration;
		std::vector<State*> statesNetwork;
		State* currentState= nullptr;
		StateEngine(EventEngine *eventengine_);
		void AddState(State *state_); 
		void SetStateNetwork();
		bool TriggerFrameChangeOnKeyPress(int keycode_);
		bool CheckFrameUpdate();
		bool NextFrame();
		
		void ElaborateStateChanges();
		void UpdateVBatFrame(AnimatedObject2D* animObj) ;
		void ChangeState(bool &wentTimeOut);
		void IsIdle(int i);

	
	 
	
	//Topological Routine
	//void NextFrame(int idx);	
	//void ConnectStatetoState(int i, int j);

};


#endif

