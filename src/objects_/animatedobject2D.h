#ifndef ANIMATEDOBJECT2D
#define ANIMATEDOBJECT2D
#include "./vectorizedobject.h"

class StateEngine;

class  AnimatedObject2D  : virtual public VectorizedObject
{
	public:

	AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,int vertxsup_,StateEngine *selfstateengine_ );
	StateEngine *selfStateEngine;	


};


#endif
