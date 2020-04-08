/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates an axis-aligned bounding box that determines collisions that may occur
  with other bounding boxes. It will calculate the min and max values of the bounding box which
  are then used to calculate for collision, using a particular formula. For the min and max values
  to be correctly calculated, the position and dimension of the box need to be set and for that 
  there is a SetPosition() and SetDimension() routine, respectively. Each one will internally call
  the CreateBox() function that will calculate the min and max values. This is so that each time
  the position or dimension change, the bounding box volume is correctly updated. The IsColliding()
  function does all of the work and uses the min and max X and Y values within a formula to 
  calculate for collision. Note that the min and max calculations are flipped on the y axis compared
  to the original OpenGL Handmade Game Engine, because the y axis is flipped in SDL.

- There is a need for a seprate private CreateBox() routine so that the min and max values can be 
  determined. If the min and max values are calculated only in the IsColliding() routine, then the
  second box's min and max values will never be known, as you would have to call both IsColliding()
  functions at once - which is very impractical. The Sphere class on the other hand only needs the
  position and radius so no seprate CreateSphere() routine is needed. 

*/

#ifndef AABB_H
#define AABB_H

#include <glm.hpp>

class AABB
{

public :

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

public :

	bool IsColliding(const AABB& secondBox);

private :

	void CreateBox();

private :

	glm::vec2 m_min;   
	glm::vec2 m_max;
	glm::vec2 m_position;
	glm::vec2 m_dimension;
	
};

#endif