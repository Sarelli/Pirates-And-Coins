#include "Sphere.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sphere::Sphere()
{

	m_radius = 0.0f;
	
}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetRadius(float radius)
{

	m_radius = radius;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns position of sphere
//------------------------------------------------------------------------------------------------------
void Sphere::SetPosition(int x, int y)
{

	m_position.x = (float)x;
	m_position.y = (float)y;

}
//------------------------------------------------------------------------------------------------------
//function that checks if sphere collides with another sphere object
//------------------------------------------------------------------------------------------------------
bool Sphere::IsColliding(const Sphere& secondSphere)
{

	//first calculate distance between both spheres and store that temporarily
	float distance = glm::length((m_position + m_radius) - 
		                         (secondSphere.m_position + secondSphere.m_radius));

	//return collision flag based on distance and radii formula  
	return (distance <= (m_radius + secondSphere.m_radius));

}