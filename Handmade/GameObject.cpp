#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

//these functions are not used at the moment
void GameObject::Initialise()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}

void GameObject::Destroy()
{
}

void GameObject::SetPosition(int X, int Y)
{
	x = X;
	y = Y;
}
