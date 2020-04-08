/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates animation objects and derives from the Sprite base class. Animations 
  generally use spritesheets with multiple images and loop through them either endlessly or for 
  one cycle only. This setting can be set externally from the client code. The animation speed can 
  also be set externally. 

- The IsAnimationLooping() function returns a bool reference variable, which makes this routine a 
  getter/setter. This makes setting the flag in the client code a lot easier. The IsAnimationDead()
  function can be called from the client code to determine if an animation is complete so that the
  game object that contains it may be destroyed. This is needed so that the game object is only
  destroyed once its animation components has finished rendering. For example an asteroid game 
  object first needs to render its explosion animation before its removed from memory.

- Because the texture index value is calculated differently here than in the Sprite base class, the 
  Draw() function is overriden. There are a few other checks inside the Draw() routine that check
  whether the animation loops or not. Sometimes an animation will loop endlessly (like a player's 
  walk cycle) or just loop once (like an explosion). When the animation is set to loop only once,
  the first texture cell in the animation has to come around again before the animation is finally
  set to end. This is because if we were to end it at the last cell, the last cell wouldn't be drawn
  so instead we let the entire spritesheet draw before killing the animation.

*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Sprite.h"

class Animation : public Sprite
{

public:

	Animation();
	virtual ~Animation() {}

public:

	bool IsAnimationDead();
	bool& IsAnimationLooping();
	void SetAnimationVelocity(float velocity);
	
public:

	virtual void Draw(int xPosition = 0, int yPosition = 0, 
		              double angle = 0.0, FlipType flipType = NO_FLIP);

protected:

	bool m_isAnimationDead;
	bool m_isAnimationLoopFinal;
	bool m_isAnimationLooping;
	
	double m_timeElapsed;
	float m_animationVelocity;

};

#endif