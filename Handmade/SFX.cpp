#include <iostream>
#include "AudioManager.h"
#include "SFX.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
SFX::SFX()
{

	m_sfx = nullptr;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets volume of sound effect
//------------------------------------------------------------------------------------------------------	
void SFX::SetVolume(int volume)
{

	Mix_VolumeChunk(m_sfx, volume);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns audio to sound effect object based on index value passed
//------------------------------------------------------------------------------------------------------
void SFX::SetSFX(const std::string& mapIndex)
{

	m_sfx = TheAudio::Instance()->GetSFXData(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//function that plays the sound effect
//------------------------------------------------------------------------------------------------------
bool SFX::Play(int loop)
{

	//if playing sound effect fails, display error message and return false
	if (Mix_PlayChannel(-1, m_sfx, loop) == -1)
	{
		std::cout << "Sound effect could not be played." << std::endl;
		return false;
	}

	return true;

}