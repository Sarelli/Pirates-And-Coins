/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a sphere colliding volume that determines collisions that may occur 
  between two spheres. It will make use of the position and radius of either sphere and use a 
  particular formula in the IsColliding() routine to check if the two spheres collide. Because the
  objects in SDL all have a position at the top left corner of the sprite or image, the sphere's
  collision volume needs to perform an extra calculation to use the centre position of each sphere
  instead. This is all handled within the IsColliding() routine.

*/

#ifndef SPHERE_H
#define SPHERE_H

#include <glm.hpp>

class Sphere
{

public :

	Sphere();

public :

	void SetRadius(float radius);
	void SetPosition(int x, int y);

public :

	bool IsColliding(const Sphere& secondSphere);

private :

	float m_radius;
	glm::vec2 m_position;

};

#endif