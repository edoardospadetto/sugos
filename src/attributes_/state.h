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


#ifndef STATE
#define STATE

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "../include/enums.h"

class Texture;
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
	State(int row_, int col_, int wpx_, int hpx_, Texture *texture_);
	void SetFrameSizePx(int sizex_, int sizey_);
	void SetFrameSize(float sizex_, float sizey_);
	void Parser(const std::string& token_, int namedatainfo_[] );
	void UpdateFrame(AnimatedObject2D* animObj);
	void ConnectTo(State* p_stat, SDL_Scancode key, Direction whichdirection);
	void ConnectOnTimeOutTo(State* p_stat);
	Texture* GetTexture();
	unsigned int GetCurrentFrameDuration();
	std::vector<State*> subsequents;
	std::vector<SDL_Scancode> edges;
	std::vector<Direction> direction;
	
	
	
};


#endif



