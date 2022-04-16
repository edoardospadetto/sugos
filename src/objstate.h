// State object related classes and code

/* 
*
* Sequence of frames, an animation for a state/action.
* Info on animations, info on image, just loads and contain
* If duration = 0, the duration of the frame is infinite.
*
* In general sets the State of an object
*
*
*
*/

class AnimatedObject2D;
class State;
class State 
{
	private:
	
	
	
		  
	
	std::vector<unsigned int> duration;
	
	Texture* stateTexture;
	
	
	public:
	
	
	std::string imgPath;
	std::string name;
	int wpx; // of snapshot
	int hpx;
	float w; 
	float h;
	
	
	int frameNum=0;
	int currentFrame = -1; 
	int x=-1; //frame
	int y=-1;
	std::vector<int> row;  // integer index.  
	std::vector<int> col;
	void AddSubsequent(State* p_snap);
	void UpdateFrame();
	 
	
	State(const std::string& confFile_,  Texture* texture_);
	void SetFrameSizePx(int sizex_, int sizey_);
	void SetFrameSize(float sizex_, float sizey_);
	void Parser(const std::string& token_, int namedatainfo_[] );
	void UpdateFrame(AnimatedObject2D* animObj);
	void ConnectTo(State* p_stat);	
	unsigned int GetCurrentFrameDuration();
	std::vector<State*> subsequents;
	
};



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
	Window_Class *window=nullptr;
	unsigned int* clock;
	int* State_duration;
	std::vector<State*> statesNetwork;
	int currentState=-1;
	StateEngine(Window_Class *window);
	void AddState(State *state_); 
	void SetStateNetwork();
	void AnimateState();
	void ElaborateStateChanges();
	void UpdateVBatFrame(AnimatedObject2D* animObj) ;
	
	//Topological Routine
	//void NextFrame(int idx);	
	//void ConnectStatetoState(int i, int j);

};

/*
* Add frame, texture, coordinate in the texture, in pixels
*
*
*
*/
/*
void StateEngine::AddState(int row_,int col_,int w_,int h_,unsigned int duration_,GLuint textureId_)
{
	frames.push_back(State {row_,col_,w_, h_,duration_,textureId_);
}
*/
// Starts counting from 0
/*
void  StateEngine::ConnectStatetoState(int i, int j)
{
	if (i < frames.size() && j < frames.size() ) frames[i].ConnectTo(&(frames[j]));
}
*/	
/*
void RunEngine(int idx)
{

}
*/
/*StateAnimation::StateAnimation(const std::string& conf_path_ , const std::string&  spritesheet_path_ ) : conf_path(conf_path_), spritesheet_path  (spritesheet_path_ )
{
	
	


}
*/


