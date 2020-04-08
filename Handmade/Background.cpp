#include "Background.h"
#include "Character.h"

Background::Background(std::string file, std::string music)
{
	x = 0;
	y = 0;
	r = 0.0;
	
	m_background = new Sprite;
	fileName = file;
	bgMusic = music;
	m_soundtrack = new Audio;
}

Background::~Background()
{
}


void Background::Initialise()
{
	m_background->SetTexture(fileName);
	m_background->SetTextureDimension(2, 1, 2388/2, 1688); //width and height of 1 cell
	m_background->SetTextureCell(0, 0);
	m_background->SetSpriteDimension(800, 800);

	m_soundtrack->SetAudio(bgMusic, Audio::MUSIC_AUDIO);
	m_soundtrack->SetVolume(25);

	m_endMap.SetPosition(800, 450);
	m_endMap.SetDimension(10, 10);

	m_beginMap.SetPosition(10, 450);
	m_beginMap.SetDimension(10, 10);
}

void Background::Update()
{
	m_soundtrack->Play(Audio::PLAY_ENDLESS);
}

void Background::Draw()
{
	m_background->Draw(x, y, r);
}

void Background::Destroy()
{
	delete m_background;
	delete m_soundtrack;
}

void Background::Switch()
{
	m_background->SetTextureCell(1, 0);
}

void Background::SwitchBack()
{
	m_background->SetTextureCell(0, 0);
}
