#include "./animatedobject2D.h"
#include "../engines_/stateengine.h"
#include "../attributes_/state.h"
#include "../attributes_/texture.h"
AnimatedObject2D::AnimatedObject2D(int vertex_len_,int vertex_num_,int surfaces_num_,int space_dim_,GLenum vertxsup_ , StateEngine *selfstateengine_) : 
VectorizedObject( vertex_len_, vertex_num_, surfaces_num_, space_dim_, vertxsup_), selfStateEngine(selfstateengine_)
{
	
};

void AnimatedObject2D::RenderTexture()
{
	this->selfStateEngine->currentState->GetTexture()->RenderTexture(0);
}
void AnimatedObject2D::UnbindTexture()
{
	this->selfStateEngine->currentState->GetTexture()->UnbindTexture();
}

bool AnimatedObject2D::HasAnimationRestarted()
{
	return this->animationRestarted;
}

void AnimatedObject2D::SetAnimationRestarted(bool hasit_)
{
	this->animationRestarted=hasit_;
}
