#include "Enemy.h"

Enemy::Enemy(int score, std::string sprite, std::string sound)
{
	x = 750;
	y = 470;
	r = 0.0;
	
	m_enemy = new Sprite;
	m_enemySfx = new SFX;
	m_enemyScore = score;
	m_enemySprite = sprite;
	m_enemySound = sound;

	m_enemyCollision.SetDimension(10, 150);
}

Enemy::~Enemy()
{
}

void Enemy::Initialise()
{
	m_enemy->SetTexture(m_enemySprite);
	m_enemy->SetTextureDimension(1, 1, 300, 300); //width and height of 1 cell
	m_enemy->SetTextureCell(0, 0); // selects the frame
	m_enemy->SetSpriteDimension(150, 150); //schale the design up or down

	m_enemySfx->SetSFX(m_enemySound);
	m_enemySfx->SetVolume(25);
}

void Enemy::Update()
{
	x--;
	if (x < -100) {
		x = 800;
	}
}

void Enemy::Draw()
{
	m_enemy->Draw(x, y, r, Sprite::HORIZONTAL);
	m_enemyCollision.SetPosition(x+50, y);
}

void Enemy::Destroy()
{
	delete m_enemy;
	delete m_enemySfx;
}

void Enemy::ResetEnemy()
{
	SetPosition(870, 470);
}
