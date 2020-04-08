/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates text objects that are able to store and display regular text strings on
  screen using a TTF font pointer that references a particular font style and size. It uses the 
  font style, a particular text color and a string of text to create a texture that will be drawn
  on screen, almost like a sprite. However this class does not derive from the Sprite class, unlike 
  the OpenGL version of Handmade, as it shares very little functionality with the Sprite class.

- There are a few setter functions to set the various properties of the text object. The SetFont()
  routine is used to assign a TTF font object to the text object. This pointer is requested from the 
  Texture Manager. Whenever the color and text are set, via SetColor() and SetText(), the internal
  CreateText() function is called each time, so that the text object can be re-created before it's
  drawn in the Draw() routine. There is no need to re-create the text each frame, as this becomes
  expensive considering the work needed to create the text object.

- The CreateText() function will create a text object and store it as a regular SDL surface before
  it's converted into a SDL texture. This texture is then used to render on screen, just like a 
  sprite renders its images on screen. Because there is a lot of loading and unloading SDL objects 
  in this routine, it becomes expensive to call it each frame, so its only called when needed, ie
  when the color or text string of the text object changes.

*/

#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <glm.hpp>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{

public :

	Text();

public :

	void SetSize(int width, int height);
	void SetText(const std::string& text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetFont(const std::string& mapIndex);
	
public :

	void Draw(int xPosition = 0, int yPosition = 0);

protected :

	void CreateText();

private :
	
	std::string m_text;
	glm::vec2 m_textSize;

	TTF_Font* m_font;
	SDL_Color m_color;
	SDL_Texture* m_texture;

};

#endif