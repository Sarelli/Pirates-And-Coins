#include "Animation.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Animation::Animation()
{

	//set other default values
	m_isAnimationDead = false;
	m_isAnimationLoopFinal = false;
	m_isAnimationLooping = true;
	
	m_timeElapsed = 0.0;
	m_animationVelocity = 0.0f;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag variable stating if animation is dead 
//------------------------------------------------------------------------------------------------------
bool Animation::IsAnimationDead()
{

	return m_isAnimationDead;

}
//------------------------------------------------------------------------------------------------------
//getter-setter function that returns looping flag variable reference
//------------------------------------------------------------------------------------------------------
bool& Animation::IsAnimationLooping()
{

	return m_isAnimationLooping;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns speed of animation
//------------------------------------------------------------------------------------------------------
void Animation::SetAnimationVelocity(float velocity)
{

	m_animationVelocity = velocity;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual animation on screen
//------------------------------------------------------------------------------------------------------
void Animation::Draw(int xPosition, int yPosition, double angle, FlipType flipType)
{

	//store the total time elapsed since animation began which will be used in formula below
	//this has been hardcoded for now so that it works with a very empty engine (to be changed!!)
	m_timeElapsed += 0.01f;

	//aquire index value of specific texture cell to "cut out" using a formula
	m_textureIndex = (int)(m_timeElapsed * m_animationVelocity) %
		             (int)(m_textureDimension.x * m_textureDimension.y);

	//if animation is set to cycle endlessly then set the kill and final flags
	//to false so that no other final checks are made and that the animation loops
	if (m_isAnimationLooping)
	{
		m_isAnimationDead = false;
		m_isAnimationLoopFinal = false;
	}

	//otherwise if animation is set to cycle once and the last texture
	//cell has been reached then flag this as the final animation loop
	else if (!m_isAnimationLooping && 
		     m_textureIndex == (m_textureDimension.x * m_textureDimension.y - 1))
	{
		m_isAnimationLoopFinal = true;
	}

	//if this is the final animation, flag to kill entire animation
	//because even though the animation is marked final, a few more 
	//frames will be called with the last texture cell set, so only
	//mark it dead when the first texture cell comes around again
	if (m_isAnimationLoopFinal && m_textureIndex == 0)
	{
		m_isAnimationDead = true;
	}

	//if animation is set to run, then render 
	//the sprite using the base class blit routine
	if (!m_isAnimationDead)
	{
		BlitSprite(xPosition, yPosition, angle, flipType);
	}

}