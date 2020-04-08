#include "Character.h"
#include "GameManager.h"

Character::~Character()
{
}

Character::Character(std::string file)
{
	x = 90;
	y = 450;
	r = 0;

	a = 175;
	b = 205;

	m_character = new Animation;
	//m_voice = new SFX;
	fileName = file;

}

void Character::Initialise()
{
	m_character->SetTexture(fileName);
	m_character->SetTextureDimension(7, 1, 3500/7, 820); //width and height of 1 cell
	m_character->SetTextureCell(0, 0); // selects the frame
	m_character->SetSpriteDimension(a, b); //schale the design up or down
	m_character->SetAnimationVelocity(0);

}

void Character::Update()
{
	if (TheGame::Instance()->CheckKey(SDL_SCANCODE_LEFT))
	{
		x -= 2;
		f = Sprite::HORIZONTAL;
		m_character->SetAnimationVelocity(20);
	}
	else if (TheGame::Instance()->CheckKey(SDL_SCANCODE_RIGHT))
	{
		x += 2;
		f = Sprite::NO_FLIP;
		m_character->SetAnimationVelocity(20);
	}
	else
	{
		m_character->SetAnimationVelocity(0);
	}

	if (x > 750)
	{
		backgroundSwitch = true;
		x = 0;
		shouldReset = true;
	}
	else if (x < 0)
	{
		backgroundSwitch = false;
		x = 700;
		shouldReset = true;
	}

}

void Character::Draw()
{
	m_character->Draw(x, y, r, f);
	m_collision.SetPosition(x, y);
	m_collision.SetDimension(a - 50, b);
}

void Character::Destroy()
{
	delete m_character;
	//delete m_voice;
}

bool Character::CheckCollision(Item* secondObject)
{
	return m_collision.IsColliding(secondObject->m_coinCollision);
}

bool Character::CheckHit(Enemy* secondObject)
{
	return m_collision.IsColliding(secondObject->m_enemyCollision);
}
