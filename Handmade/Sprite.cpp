#include "Sprite.h"
#include "ScreenManager.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{

	m_textureIndex = 0;
	m_texture = nullptr;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns specific position of image cell in texture
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureCell(int column, int row)
{

	m_textureCell.x = (float)column;
	m_textureCell.y = (float)row;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns texture image to sprite based on index value passed
//------------------------------------------------------------------------------------------------------
void Sprite::SetTexture(const std::string& mapIndex)
{

	m_texture = TheTexture::Instance()->GetTexture(mapIndex);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns size of sprite
//------------------------------------------------------------------------------------------------------
void Sprite::SetSpriteDimension(int width, int height)
{

	m_spriteDimension.x = (float)width;
	m_spriteDimension.y = (float)height;

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns dimension size of texture and pixel size of each cell
//------------------------------------------------------------------------------------------------------
void Sprite::SetTextureDimension(int column, int row, int width, int height)
{

	m_textureDimension.x = column;
	m_textureDimension.y = row;
	m_textureDimension.w = width;
	m_textureDimension.h = height;

}
//------------------------------------------------------------------------------------------------------
//function that creates and draws the actual sprite on screen
//------------------------------------------------------------------------------------------------------
void Sprite::Draw(int xPosition, int yPosition, double angle, FlipType flipType)
{

	//aquire index value of specific texture cell to "cut out" using a basic formula 
	m_textureIndex = (int)((m_textureCell.y * m_textureDimension.x) + m_textureCell.x);

	//use internal blitting function to draw the sprite on screen
	BlitSprite(xPosition, yPosition, angle, flipType);

}
//------------------------------------------------------------------------------------------------------
//function that calculates the source and destination sections of the sprite and screen and renders
//------------------------------------------------------------------------------------------------------
void Sprite::BlitSprite(int xPosition, int yPosition, double angle, FlipType flipType)
{

	//variables to store rectangular dimensions for the source 
	//sprite and destination portion of the screen to render to 
	SDL_Rect src;
	SDL_Rect dst;

	//use modulo and divide with the texture index to get exact cell block XY coordinates
	//to "cut out" and assign all of this as well as width and height to the source rect
	src.x = (int)((m_textureIndex % (int)m_textureDimension.x) * m_textureDimension.w);
	src.y = (int)((m_textureIndex / (int)m_textureDimension.x) * m_textureDimension.h);
	src.w = m_textureDimension.w;
	src.h = m_textureDimension.h;

	//assign dimension of rectangular block to which sprite will be rendered to on screen
	dst.x = xPosition;
	dst.y = yPosition;
	dst.w = (int)m_spriteDimension.x;
	dst.h = (int)m_spriteDimension.y;

	//if sprite needs to be rotated, use the centre of the sprite as its centre of rotation
	SDL_Point centrePoint;
	centrePoint.x = (int)m_spriteDimension.x / 2;
	centrePoint.y = (int)m_spriteDimension.y / 2;

	//render the sprite using all values passed and determined above
	SDL_RenderCopyEx(TheScreen::Instance()->GetRenderer(), 
		             m_texture, &src, &dst, angle, &centrePoint, (SDL_RendererFlip)flipType);

}