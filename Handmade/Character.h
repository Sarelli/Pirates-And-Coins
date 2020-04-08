#pragma once
#include <string>
#include <iostream>
#include "GameObject.h"
#include "Animation.h"
#include "SFX.h"
#include "AABB.h"
#include "Item.h"
#include "Enemy.h"

class Character : public GameObject
{
public:
	Character(std::string file);
	~Character();

	void Initialise();
	void Update();
	void Draw();
	void Destroy();

	//Getters and Setters
	bool GetBGSwitch() { return backgroundSwitch; }
	bool GetShouldReset() { return shouldReset; }
	void SetShouldReset(bool param) { shouldReset = param; } //it is supposed to be a RESET since it doesn't have a parameter
	
	//Colliders
	bool CheckCollision(Item* secondObject);
	bool CheckHit(Enemy* secondObject);

private:
	Animation* m_character;
	//SFX* m_voice;
	std::string fileName;
	Sprite::FlipType f;
	AABB m_collision;

	int a;
	int b;

	bool backgroundSwitch;
	bool shouldReset;

};

