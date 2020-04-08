#include <iostream>
#include "Audio.h"
#include "AudioManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Audio::Audio()
{

	m_audio = nullptr;

}
//------------------------------------------------------------------------------------------------------
//setter function that sets volume of audio
//------------------------------------------------------------------------------------------------------
void Audio::SetVolume(int volume)
{

	Mix_VolumeMusic(volume);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns audio to music or voice object based on index value passed
//------------------------------------------------------------------------------------------------------
void Audio::SetAudio(const std::string& mapIndex, AudioType audioType)
{

	audioType == MUSIC_AUDIO ? m_audio = TheAudio::Instance()->GetMusicData(mapIndex)
							 : m_audio = TheAudio::Instance()->GetVoiceData(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//function that plays music 
//------------------------------------------------------------------------------------------------------
bool Audio::Play(LoopType loopType)
{

	//check if music is not already playing
	if(!Mix_PlayingMusic())
	{

		//if playing music fails, display error message and return false
		if(Mix_PlayMusic(m_audio, loopType) == -1)
		{
			std::cout << "Music could not be played." << std::endl;
			return false;
		}

	}
	
	return true;

}
//------------------------------------------------------------------------------------------------------
//function that pauses the playing music 
//------------------------------------------------------------------------------------------------------
void Audio::Pause()
{

	//check if music is not already paused
	if(!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}

}
//------------------------------------------------------------------------------------------------------
//function that resumes the music after a paused state
//------------------------------------------------------------------------------------------------------
void Audio::Resume()
{

	//check if music is paused
	if(Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}

}
//------------------------------------------------------------------------------------------------------
//function that stops playing music 
//------------------------------------------------------------------------------------------------------
void Audio::Stop()
{

	//check if music is playing
	if(Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

}