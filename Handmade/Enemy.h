#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "SFX.h"
#include "AABB.h"

class Enemy : public GameObject 
{
public:
	Enemy(int score, std::string sprite, std::string sound);
	~Enemy();

	void Initialise();
	void Update();
	void Draw();
	void Destroy();

	void ResetEnemy();
	int ReturnX() { return x; }

	int ReturnScore() { return m_enemyScore; }
	SFX* PlayHit() { return m_enemySfx; }
	AABB m_enemyCollision;

private:
	Sprite* m_enemy;
	SFX* m_enemySfx;
	int m_enemyScore;
	std::string m_enemySprite;
	std::string m_enemySound;
};

