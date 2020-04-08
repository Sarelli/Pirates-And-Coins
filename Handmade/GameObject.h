#pragma once
#include "Animation.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Initialise(); //could be done using constructor
	virtual void Update();
	virtual void Draw();
	virtual void Destroy(); //could be done using decontructor

	//Getter
	void SetPosition(int X, int Y);

protected: //these will be accessible ONLY from inheriting (CHILD) classes
	int x;
	int y;
	int r;
};

