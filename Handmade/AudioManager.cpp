#include <iostream>
#include "AudioManager.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to sound effect data based on index value passed
//------------------------------------------------------------------------------------------------------
Mix_Chunk* AudioManager::GetSFXData(const std::string& mapIndex)
{

	return m_sfxDataMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to music data based on index value passed
//------------------------------------------------------------------------------------------------------
Mix_Music* AudioManager::GetMusicData(const std::string& mapIndex)
{

	return m_musicDataMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to voice data based on index value passed
//------------------------------------------------------------------------------------------------------
Mix_Music* AudioManager::GetVoiceData(const std::string& mapIndex)
{

	return m_voiceDataMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//function that initializes SDL audio sub-system 
//------------------------------------------------------------------------------------------------------
bool AudioManager::Initialize()
{

	//if audio sub-system initialization failed, display error message and return false
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1)
	{
		std::cout << "Audio sub-system did not initialize properly." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that loads music, sfx and voice audio data from a raw audio file 
//------------------------------------------------------------------------------------------------------	
bool AudioManager::LoadFromFile(const std::string& filename, AudioType audioType, 
	                            const std::string& mapIndex)
{

	//display text to state that file is being opened and read
	std::cout << "Opening and reading audio file : " << "\"" << filename << "\"" << std::endl;

	//if a sfx file needs to be loaded, load it into memory and check
	//if it was loaded properly before adding it to the sfx data map 
	if (audioType == SFX_AUDIO)
	{
		
		Mix_Chunk* sfx = Mix_LoadWAV(filename.c_str());

		if (!sfx)
		{
			std::cout << "File could not be loaded." << std::endl;
			std::cout << "---------------------------------------------------------------" << std::endl;
			return false;
		}

		m_sfxDataMap[mapIndex] = sfx;

	}

	//otherwise if a music or voice file needs to be loaded, load it into memory and
	//check if it was loaded properly before adding it to the music/voice data map 
	else if (audioType == MUSIC_AUDIO || audioType == VOICE_AUDIO)
	{

		Mix_Music* audio = Mix_LoadMUS(filename.c_str());

		if (!audio)
		{
			std::cout << "File could not be loaded." << std::endl;
			std::cout << "---------------------------------------------------------------" << std::endl;
			return false;
		}

		audioType == MUSIC_AUDIO ? m_musicDataMap[mapIndex] = audio
							     : m_voiceDataMap[mapIndex] = audio;

	}

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that unloads single or multiple audio objects from memory
//------------------------------------------------------------------------------------------------------
void AudioManager::UnloadFromMemory(AudioType audioType, 
	                                RemoveType removeType, const std::string& mapIndex)
{

	//if a sfx file needs to be removed, free it from memory based on if a 
	//single item needs to be removed or if the entire map needs to be cleared
	if (audioType == SFX_AUDIO)
	{

		if (removeType == CUSTOM_AUDIO)
		{
			auto it = m_sfxDataMap.find(mapIndex);
			
			if (it == m_sfxDataMap.end())
			{
				std::cout << "Audio data not found." << std::endl;
			}

			else
			{
				Mix_FreeChunk(it->second);
				m_sfxDataMap.erase(it);
			}
		}

		else if (removeType == ALL_AUDIO)
		{
			
			for (auto it = m_sfxDataMap.begin(); it != m_sfxDataMap.end(); it++)
			{
				Mix_FreeChunk(it->second);
			}

			m_sfxDataMap.clear();

		}

	}

	//otherwise if a music or voice file needs to be removed, free it from memory based
	//on if a single item needs to be removed or if the entire map needs to be cleared
	//we use a temporary map pointer so that we don't rewrite code for two different maps
	else if (audioType == MUSIC_AUDIO || audioType == VOICE_AUDIO)
	{

		std::map<std::string, Mix_Music*>* tempMap = nullptr;

		audioType == MUSIC_AUDIO ? tempMap = &m_musicDataMap
							     : tempMap = &m_voiceDataMap;

		if (removeType == CUSTOM_AUDIO)
		{
			auto it = tempMap->find(mapIndex);

			if (it == tempMap->end())
			{
				std::cout << "Audio data not found." << std::endl;
			}

			else
			{
				Mix_FreeMusic(it->second);
				tempMap->erase(it);
			}
		}

		else if (removeType == ALL_AUDIO)
		{

			for (auto it = tempMap->begin(); it != tempMap->end(); it++)
			{
				Mix_FreeMusic(it->second);
			}

			tempMap->clear();

		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL audio sub-system
//------------------------------------------------------------------------------------------------------
void AudioManager::ShutDown()
{

	Mix_CloseAudio();

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of all audio data maps
//------------------------------------------------------------------------------------------------------
void AudioManager::Output()
{

	system("cls");
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Total size of all audio maps : " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Size of SFX Data Map   : " << m_sfxDataMap.size() << std::endl;
	std::cout << "Size of Music Data Map : " << m_musicDataMap.size() << std::endl;
	std::cout << "Size of Voice Data Map : " << m_voiceDataMap.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}