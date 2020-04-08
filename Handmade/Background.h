#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Audio.h"
#include "AABB.h"
#include <string>

class Background : public GameObject
{
public:
	Background(std::string file, std::string music);
	~Background();

	void Initialise();
	void Update();
	void Draw();
	void Destroy();

	void Switch();
	void SwitchBack();
	//bool MapCollision(Character* secondObject);

private:
	Sprite* m_background;
	std::string fileName;
	std::string bgMusic;
	Audio* m_soundtrack;

	AABB m_endMap;
	AABB m_beginMap;
};

