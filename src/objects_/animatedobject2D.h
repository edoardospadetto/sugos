#ifndef ANIMATEDOBJECT2D
#define ANIMATEDOBJECT2D
#include "./vectorizedobject.h"

class StateEngine;

class  AnimatedObject2D  : virtual public VectorizedObject
{
	bool animationRestarted=false;
	public:
	
	AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_,StateEngine *selfstateengine_ );
	StateEngine *selfStateEngine;	

	void RenderTexture();
	void UnbindTexture();
	bool HasAnimationRestarted();
	void SetAnimationRestarted(bool hasit_);
	
	friend class StateEngine;
};


#endif
