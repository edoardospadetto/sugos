
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





// Animation related classes and code

/* 
*
* Engine to hangle animations of a single object.
* One state many frame, engine knows all the state for an object
* 
* Thought to be symbiotic with AnimObj
*
*/

class StateEngine
{	
	private:
	
	unsigned int frameInit;
	
	public:
	
	SDL_Scancode animGen;
	Window_Class *window=nullptr;
	unsigned int* clock;
	int* State_duration;
	std::vector<State*> statesNetwork;
	State* currentState= nullptr;
	StateEngine(Window_Class *window);
	void AddState(State *state_); 
	void SetStateNetwork();
	void AnimateState(bool &wentTimeOut);
	void ElaborateStateChanges();
	void UpdateVBatFrame(AnimatedObject2D* animObj) ;
	void ChangeState(bool &wentTimeOut);
	void IsIdle(int i);
	
	 
	
	//Topological Routine
	//void NextFrame(int idx);	
	//void ConnectStatetoState(int i, int j);

};




