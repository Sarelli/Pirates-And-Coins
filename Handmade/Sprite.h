/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates sprite objects and uses a texture pointer to represent the actual 
  sprite image. The image can be a single image, or a spritesheet of multiple images, which is
  great for animations. The main aim of this class is to be able to assign single images or a 
  specific spritesheet cell image to be used. The Sprite class is a base class from which the 
  Animation class derives from. 

- The enumerated type is there to set the sprite orientation. Either the sprite will be rendered
  as is, or it can be flipped on the horizontal or vertical axis. This value can be set directly
  in the Draw() function when the sprite gets rendered.

- One of the most important member variables is the texture index variable. It is the index value
  of the actual sprite cell of a sprite sheet, if the texture image has multiple images within. 
  If the texture image is singular, the texture index is 0 by default. The texture index is zero 
  based and is a whole number value counting from top left and going right and down the spritesheet. 
  It is calculated differently in the base class to the Animation sub-class. 

- The setter functions will set the specific properties of the sprite. The SetTexture() routine is
  used to assign an SDL texture object to the sprite object. This pointer is requested from the 
  Texture Manager. The SetTextureDimension() will set the dimension of the texture in terms of rows
  and colums. A single texture will be 1x1 but a spritesheet might have multiple columns and rows. 
  The function also takes in the dimension of each texture cell and if its a singular texture, the
  dimension will be the total dimension of the texture. This has been dramatically changed in 
  comparison to the original Handmade engine code, because in OpenGL we work with normalized values
  and here we deal with full pixel values and sizes. The SetSpriteDimension() routine is there to 
  assign the size of the sprite as it should appear on screen.

- The Draw() function is different in all the classes, therefore it will be virtually overriden 
  based on what object type is being used. The base class and the sub-class all calculate the 
  texture index differently. The function will call the internal BlitSprite() routine which takes the
  sprite and screen render destination dimensions and calculates how to "cut out" the sprite and how
  to display it accordingly on screen. 

*/

#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <glm.hpp>
#include <SDL.h>

class Sprite
{

public :

	enum FlipType { NO_FLIP, HORIZONTAL, VERTICAL };

public :

	Sprite();           
	virtual ~Sprite() {}

public :

	void SetTextureCell(int column, int row);
	void SetTexture(const std::string& mapIndex);
	void SetSpriteDimension(int width, int height);
	void SetTextureDimension(int column, int row, int width, int height);
	
public :

	virtual void Draw(int xPosition = 0, int yPosition = 0, 
		              double angle = 0.0, FlipType flipType = NO_FLIP);

protected :

	void BlitSprite(int xPosition, int yPosition, double angle, FlipType flipType);

protected :

	int m_textureIndex;

	glm::vec2 m_textureCell;
	glm::vec2 m_spriteDimension;

	SDL_Texture* m_texture;
	SDL_Rect m_textureDimension;

};

#endif