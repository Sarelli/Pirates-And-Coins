#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "SFX.h"
#include "AABB.h"

class Item : public GameObject
{
public:
	Item(int score, std::string sprite, std::string sound);
	~Item();

	void Initialise();
	void Update();
	void Draw();
	void Destroy();

	void ResetCoin();

	int ReturnScore() { return m_coinScore; }
	SFX* PlayCoin() { return m_coinSfx; }
	AABB m_coinCollision;

private:
	Sprite* m_item;
	SFX* m_coinSfx;
	int m_coinScore;
	std::string m_coinSprite;
	std::string m_coinSound;

};

