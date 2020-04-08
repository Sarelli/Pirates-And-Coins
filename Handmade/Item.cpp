#include "Item.h"
#include "GameManager.h"
#include <cstdlib>
#include <ctime>

Item::~Item()
{
}

Item::Item(int score, std::string sprite, std::string sound)
{
	m_item = new Sprite;
	m_coinSfx = new SFX;
	m_coinSprite = sprite;
	m_coinSound = sound;

	m_coinScore = score;
}

void Item::Initialise()
{
	x = (rand() % 800);
	y = 590;
	r = 0.0;

	m_item->SetTexture(m_coinSprite);
	m_item->SetTextureDimension(1, 1, 300, 300); //width and height of 1 cell
	m_item->SetTextureCell(0, 0); // selects the frame
	m_item->SetSpriteDimension(50, 50); //schale the design up or down

	m_coinSfx->SetSFX(m_coinSound);
	m_coinSfx->SetVolume(20);
}

void Item::Draw()
{
	m_item->Draw(x, y, r);
	m_coinCollision.SetPosition(x+25, y);
	m_coinCollision.SetDimension(5, 50);
}

void Item::Update()
{	
}

void Item::Destroy()
{
	delete m_item;
	delete m_coinSfx;
}

void Item::ResetCoin()
{
	m_item->SetSpriteDimension(0, 0);
	SetPosition(0, 0);
}
