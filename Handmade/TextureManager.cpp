#include <iostream>
#include <SDL_image.h>
#include "ScreenManager.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//getter function that returns font pointer based on font map index passed 
//------------------------------------------------------------------------------------------------------
TTF_Font* TextureManager::GetFont(const std::string& mapIndex)
{

	return m_fontMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//getter function that returns texture pointer based on texture map index passed 
//------------------------------------------------------------------------------------------------------
SDL_Texture* TextureManager::GetTexture(const std::string& mapIndex)
{

	return m_textureMap[mapIndex];

}
//------------------------------------------------------------------------------------------------------
//function that initializes SDL font sub-system 
//------------------------------------------------------------------------------------------------------
bool TextureManager::Initialize()
{

	//if font sub-system initialization failed, display error message and return false
	if (TTF_Init() == -1)
	{
		std::cout << "Font sub-system did not initialize properly." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that loads a font from a file in a particular size and stores the data in a font map
//------------------------------------------------------------------------------------------------------
bool TextureManager::LoadFontFromFile(const std::string& filename, int fontSize, 
	                                  const std::string& mapIndex)
{

	//display text to state that file is being opened and read
	std::cout << "Opening and reading font file : " << "\"" << filename << "\"" << std::endl;

	//load font from file using SDL font load function
	TTF_Font* font = TTF_OpenFont(filename.c_str(), fontSize);

	//if font loading failed, display error message and return false
	if (!font)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	//add font pointer to map for storage
	m_fontMap[mapIndex] = font;

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that loads a texture from a raw image file and stores the ID in a texture map
//------------------------------------------------------------------------------------------------------
bool TextureManager::LoadTextureFromFile(const std::string& filename, const std::string& mapIndex)
{

	SDL_Texture* texture = nullptr;
	SDL_Surface* textureData = nullptr;

	//display text to state that file is being opened and read
	std::cout << "Opening and reading texture file : " << "\"" << filename << "\"" << std::endl;

	//load texture from file using SDL image load function
	textureData = IMG_Load(filename.c_str());

	//if texture loading failed, display error message 
	if (!textureData)
	{
		std::cout << "File could not be loaded." << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
		return false;
	}

	else
	{

		//create a texture out of the previously loaded image
		texture = SDL_CreateTextureFromSurface(TheScreen::Instance()->GetRenderer(), textureData);

		//free SDL image as its no longer needed
		SDL_FreeSurface(textureData);

		//assign newly created texture object to texture map
		m_textureMap[mapIndex] = texture;

	}

	//display text to state that file has been opened and read
	std::cout << "File opened and read successfully." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that unloads single or multiple textures from memory
//------------------------------------------------------------------------------------------------------
void TextureManager::UnloadFromMemory(DataType dataType, 
	                                  RemoveType removeType, const std::string& mapIndex)
{

	//if a font file needs to be removed, free it from memory based on if a 
	//single item needs to be removed or if the entire map needs to be cleared
	if (dataType == FONT_DATA)
	{

		if (removeType == CUSTOM_DATA)
		{
			auto it = m_fontMap.find(mapIndex);

			if (it == m_fontMap.end())
			{
				std::cout << "Font data not found." << std::endl;
			}

			else
			{
				TTF_CloseFont(it->second);
				m_fontMap.erase(it);
			}
		}

		else if (removeType == ALL_DATA)
		{

			for (auto it = m_fontMap.begin(); it != m_fontMap.end(); it++)
			{
				TTF_CloseFont(it->second);
			}

			m_fontMap.clear();

		}

	}

	//otherwise if a texture file needs to be removed, free it from memory based on
	//if a single item needs to be removed or if the entire map needs to be cleared
	else if (dataType == TEXTURE_DATA)
	{

		if (removeType == CUSTOM_DATA)
		{
			auto it = m_textureMap.find(mapIndex);

			if (it == m_textureMap.end())
			{
				std::cout << "Texture data not found." << std::endl;
			}

			else
			{
				SDL_DestroyTexture(it->second);
				m_textureMap.erase(it);
			}
		}

		else if (removeType == ALL_DATA)
		{

			for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
			{
				SDL_DestroyTexture(it->second);
			}

			m_textureMap.clear();

		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL font sub-system
//------------------------------------------------------------------------------------------------------
void TextureManager::ShutDown()
{

	TTF_Quit();

}
//------------------------------------------------------------------------------------------------------
//function that displays total size of font and texture maps
//------------------------------------------------------------------------------------------------------
void TextureManager::Output()
{

	system("cls");
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Total size of texture and font maps : " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "Size of Font Map    : " << m_fontMap.size() << std::endl;
	std::cout << "Size of Texture Map : " << m_textureMap.size() << std::endl;
	std::cout << "------------------------------------" << std::endl;

}