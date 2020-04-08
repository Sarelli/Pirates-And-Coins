/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a texture manager which will load images from disk and store them as 
  SDL textures in a map, with a string reference to that texture. The images are loaded using 
  SDL's image loading function and generated through SDL's texture creation routine to produce 
  a texture object out of the SDL_Surface object that was originally loaded. SDL textures make use
  of the GPU and so are preferred. Currently the images supported are BMP, PNG, JPG, GIF, TGA. <TBA>.
  To access a particular image inside the map the string reference is needed to sift through the 
  map and find the texture. Textures can also be unloaded from memory individually or in bulk.
  Furthermore, this class also loads font files and stores them in a similar manner in a separate 
  font map. Fonts and textures are stored together because they are somewhat linked in the original
  Handmade engine, and this prevents us from creating a separate Font Manager class. This class is
  a Singleton.

- Two enum types have been created to be used when removing texture images from the map. Either
  one single specific texture can be removed, or the entire map of textures can be cleared.

- To use this class, an object in the client code will need to link to a specific texture or font 
  pointer from within the Texture Manager. The GetFont() and GetTexture() functions are used to 
  request the font and texture pointers respectively and link the data with the external object. 

- An Output() routine is there for debug purposes only and will print to the console how many font
  and texture objects are currently stored in the map.

*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Singleton.h"

class TextureManager
{

public:

	enum DataType   { FONT_DATA, TEXTURE_DATA };
	enum RemoveType { CUSTOM_DATA, ALL_DATA };

public :

	friend class Singleton<TextureManager>;

public:

	TTF_Font* GetFont(const std::string& mapIndex);
	SDL_Texture* GetTexture(const std::string& mapIndex);

public:

	bool Initialize();
	bool LoadFontFromFile(const std::string& filename, int fontSize, const std::string& mapIndex);
	bool LoadTextureFromFile(const std::string& filename, const std::string& mapIndex);
	void UnloadFromMemory(DataType dataType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public:

	void Output();

private :

	TextureManager()  {}
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

private :

	std::map<std::string, TTF_Font*> m_fontMap;
	std::map<std::string, SDL_Texture*> m_textureMap;
	
};

typedef Singleton<TextureManager> TheTexture;

#endif