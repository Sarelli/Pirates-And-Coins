#pragma once
#include "GameManager.h"
#include <cstdlib>
#include <ctime>


bool GameManager::CheckKey(int id) 
{ 
	keys = TheInput::Instance()->GetKeyStates();
	return keys[id]; 
}

void GameManager::Initialisation()
{
	srand(time(0));

	//initialize screen
	TheScreen::Instance()->Initialize(gameName.c_str(), screenWidth, screenHeight);
	TheScreen::Instance()->SetClearColor(0, 0, 0);

	//initialize textures (backgrounds)
	TheTexture::Instance()->Initialize();
	TheTexture::Instance()->LoadTextureFromFile("Assets/Textures/Dock.png", "BG0");

	//initialize sprites (item, characters)
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Pirate.png", "CHR0");
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Ghost.png", "OBJ0");
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Coin.png", "OBJ1");
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Coin5.png", "OBJ2");
	TheTexture::Instance()->LoadTextureFromFile("Assets/Sprites/Coin10.png", "OBJ3");

	//initialize audio (Music, SFX, Voice)
	TheAudio::Instance()->Initialize();
	TheAudio::Instance()->LoadFromFile("Assets/Audio/Gameloop.wav", TheAudio::Instance()->MUSIC_AUDIO, "MAIN");
	TheAudio::Instance()->LoadFromFile("Assets/Audio/Coin.wav", TheAudio::Instance()->SFX_AUDIO, "COIN");
	TheAudio::Instance()->LoadFromFile("Assets/Audio/Hit.wav", TheAudio::Instance()->SFX_AUDIO, "HIT");

	//initialize fonts
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/BradBunR.ttf", 150, "FONT0");
	TheTexture::Instance()->LoadFontFromFile("Assets/Fonts/OptimusPrinceps.ttf", 400, "FONT1");

	background = new Background("BG0", "MAIN");
	character = new Character("CHR0");
	coin1 = new Item(1, "OBJ1", "COIN");
	coin2 = new Item(5, "OBJ2", "COIN");
	coin3 = new Item(10, "OBJ3", "COIN");
	enemy = new Enemy(7, "OBJ0", "HIT");

	Items[0] = coin1;
	Items[1] = coin2;
	Items[2] = coin3;	

	background->Initialise();
	character->Initialise();
	for (int i = 0; i < 3; i++) { Items[i]->Initialise(); }
	enemy->Initialise();

	m_text = new Text;
	m_text->SetFont("FONT0");
	m_text->SetColor(30, 200, 10);
	m_text->SetSize(100, 100);
	m_text->SetText("POINTS: " + ConvertScore());

	m_instructions1 = new Text;
	m_instructions1->SetFont("FONT1");
	m_instructions1->SetColor(255, 255, 255);
	m_instructions1->SetSize(300, 80);
	m_instructions1->SetText("Collect the coins and have fun!");

	m_instructions2 = new Text;
	m_instructions2->SetFont("FONT1");
	m_instructions2->SetColor(255, 255, 255);
	m_instructions2->SetSize(340, 80);
	m_instructions2->SetText("Use the right and left arrows to move.");

	m_instructions3 = new Text;
	m_instructions3->SetFont("FONT1");
	m_instructions3->SetColor(255, 255, 255);
	m_instructions3->SetSize(330, 80);
	m_instructions3->SetText("Press Spacebar to hit the ghosts.");
}

void GameManager::Gameplay()
{
	//main game loop!
	while (!m_endGame)
	{
		//update screen by clearing SDL frame buffer - SCREEN CLEAR
		TheScreen::Instance()->Update();

		//update input handling by listening for input events
		TheInput::Instance()->Update();
		//read keyboard state
		keys = TheInput::Instance()->GetKeyStates();
		if (character->GetShouldReset())
		{
			if (character->GetBGSwitch())
			{
				background->Switch();
				enemy->ResetEnemy();
			}
			else
			{
				background->SwitchBack();
				enemy->ResetEnemy();
			}
			
			for (int i = 0; i < 3; i++) { Items[i]->Initialise(); }
			character->SetShouldReset(false);
		}

		//my objects get updated
		background->Update();
		character->Update();
		for (int i = 0; i < 3; i++) { Items[i]->Update(); }
		enemy->Update();

		//if game window's top right X is clicked or Q is pressedflag game to end
		if (TheInput::Instance()->IsXClicked() || keys[SDL_SCANCODE_Q])
		{
			m_endGame = true;
		}

		//check collision with coins
		for (int i = 0; i < 3; i++)
		{
			if (character->CheckCollision(Items[i]))
			{
				m_score = m_score + Items[i]->ReturnScore();
				m_text->SetText("POINTS: " + ConvertScore());
				m_text->Draw(30, -10);
				Items[i]->PlayCoin()->Play();
				Items[i]->ResetCoin();
			}
		}

		//check collision with enemy
		if (character->CheckHit(enemy) && !keys[SDL_SCANCODE_SPACE] && enemy->ReturnX() < 740)
		{
			m_text->SetColor(255, 10, 10);
			m_text->SetSize(300, 300);
			m_text->SetText("GAME OVER");
			m_text->Draw(1000, 800);
			character->SetPosition(-10, 1000);

		}
		else if(character->CheckHit(enemy) && keys[SDL_SCANCODE_SPACE])
		{
			m_score = m_score + enemy->ReturnScore();
			m_text->SetText("POINTS: " + ConvertScore());
			m_text->Draw(30, -10);
			enemy->PlayHit()->Play();
			enemy->ResetEnemy();
		}

		//my objects get drawn
		background->Draw();
		character->Draw();
		for (int i = 0; i < 3; i++) { Items[i]->Draw(); }
		enemy->Draw();
		m_text->Draw(30, -10);
		m_instructions1->Draw(400, 0);
		m_instructions2->Draw(400, 90);
		m_instructions3->Draw(400, 180);

		TheScreen::Instance()->Draw();

	}

	background->Destroy();
	character->Destroy();
	for (int i = 0; i < 3; i++) { Items[i]->Destroy(); }
	enemy->Destroy();
}

void GameManager::Shutdown()
{
	TheTexture::Instance()->UnloadFromMemory(TheTexture::Instance()->TEXTURE_DATA, TheTexture::Instance()->ALL_DATA); // delete all textures
	TheTexture::Instance()->UnloadFromMemory(TheTexture::Instance()->FONT_DATA, TheTexture::Instance()->ALL_DATA); // delete all fonts
	TheAudio::Instance()->UnloadFromMemory(TheAudio::Instance()->SFX_AUDIO, TheAudio::Instance()->ALL_AUDIO); // delete all SFX audio

	//close down audio 
	TheAudio::Instance()->ShutDown();

	//close down texture
	TheTexture::Instance()->ShutDown();

	delete background;
	delete character;
	delete coin1;
	delete coin2;
	delete coin3;
	delete enemy;
	delete m_text;
	delete m_instructions1;
	delete m_instructions2;
	delete m_instructions3;

	//close down game screen 
	TheScreen::Instance()->ShutDown();
}
