#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>

#include "Singleton.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "Text.h"
#include "Animation.h"
#include "SFX.h"

#include "Character.h"
#include "Background.h"
#include "Item.h"
#include "Enemy.h"
#include <array>


class GameManager
{
public:

	std::string gameName = "Pirates and Coins";
	//screen width and height values
	int screenWidth = 800;
	int screenHeight = 800;

	//other variables
	const Uint8* keys = nullptr;

	friend class Singleton<GameManager>;

	//Getters
	bool CheckKey(int id);
	bool GetEndGame() { return m_endGame;  }
	bool GetHasPlayed() { return m_hasPlayed; }

	//Game Phases
	void Initialisation();
	void Gameplay();
	void Shutdown();

	std::string ConvertScore() { return std::to_string(m_score); }

private:

	//variables
	bool m_hasPlayed = false;
	bool m_endGame = false;
	int m_score = 0;

	Background* background;
	Character* character;

	Item* coin1;
	Item* coin2;
	Item* coin3;
	Enemy* enemy;

	Text* m_text;
	Text* m_instructions1;
	Text* m_instructions2;
	Text* m_instructions3;

	Item* Items[3];
};

typedef Singleton<GameManager> TheGame;