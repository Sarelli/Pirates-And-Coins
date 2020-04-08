/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : January 2017

  -----------------------------------------------------------------------------------------------

- This is a Singleton Manager class that controls all the input from the mouse and keyboard (More
  controls later!!) It uses a set of SDL library tools to manage the input and stores the mouse 
  and keyboard values in various property variables. The class as a whole can determine what keys
  have been pressed and what state the mouse buttons are in, and these states can be queried from
  external code at any time.

- Three enumerated types have been created to be used when storing the button states of the mouse 
  buttons, the mouse cursor state, and the SDL mouse cursor flag values, whose values all correspond
  with SDL's numeric values for those specific mouse cursors.

- The class variables store all the details of the mouse and keyboard and the m_isXClicked and 
  m_isKeyPressed variables store whether the X in the top right corner of the game window has been 
  clicked or whether a keyboard key has been pressed or not respectively. The m_isKeyPressed
  variable is handy if you want to quickly check if a random key has been pressed or released as 
  opposed to checking each key's state. For that there is a separate variable called m_keyStates.
  The m_keyStates variable, which is a pointer to an array of Uint8 values, is filled each time a key
  is pressed and will store a kind of binary snapshot of the keyboard, stating which keys are pressed,
  and which are not. Each individual element in the array represents a key on the keyboard and can be 
  queried in the client code as to whether that key is pressed or not.
  Three button state variables store the pressed state of the three mouse buttons. This is perfect 
  for mouse functions, but for keyboard keys there are too many keys to individually set their state
  so for that there is a separate keystate array variable.

- For each class property variable there is a getter function for when mouse and keyboard states are
  queried in the client code. There are two IsMouseColliding() functions, both using the current mouse 
  coordinates to create either a AABB box or Sphere around that to check if the mouse collides with the
  passed bound. This is handy for checking if the mouse cursor is hovering over buttons, spherical 
  things or any other game objects. The IsMouseColliding() could have been passed a generic Bound 
  object, but then dynamic casting is needed to set the dimension each time and that is expensive! 
  Templatizing could also work but the two functions are not exactly identical. Basic function 
  overriding seems to be the best solution here for now. (More TBA)  
  There are two mouse cursor setter functions to set the type and state of the mouse cursor. Using 
  these functions, a specific Windows OS mouse cursor can be created and the cursor may be enabled, 
  disabled, shown or hidden

- The Update() function is the core of the Input Manager class. It will process all SDL events that
  build up on the event queue and will store particular keyboard and mouse property values in the 
  relevant variables. These values can then be used at any time in the client code. This routine will
  need to be called once per frame in the client code.

*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>
#include "AABB.h"
#include "Singleton.h"
#include "Sphere.h"

class InputManager
{

public :

	enum ButtonState { UP, DOWN };
	enum CursorState { ON = 1, OFF = 0, SHOW = 1, HIDE = 0 };
	enum CursorType  { ARROW, IBEAM, WAIT, CROSSHAIR, WAIT_ARROW, NO = 10, HAND = 11 };

public :

	friend class Singleton<InputManager>;

public :

	bool IsXClicked();
	bool IsKeyPressed();
	const Uint8* GetKeyStates();
	bool IsMouseColliding(const AABB& bound);
	bool IsMouseColliding(const Sphere& bound);

public :

	ButtonState GetLeftButtonState();
	ButtonState GetMiddleButtonState();
	ButtonState GetRightButtonState();

	glm::vec2 GetMousePosition();
	glm::vec2 GetMouseMotion();
	glm::vec2 GetMouseWheel();	
	
	void SetMousePosition(int x, int y);
	void SetMouseCursorType(CursorType cursorType = ARROW);
	void SetMouseCursorState(CursorState cursorEnabled = ON, CursorState cursorVisible = SHOW);

public :

	void Update();

private :

	InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);

private :

	bool m_isXClicked;
	bool m_isKeyPressed;

	const Uint8* m_keyStates;

	SDL_Cursor* m_cursor;

	ButtonState m_leftButtonState;
	ButtonState m_middleButtonState;
	ButtonState m_rightButtonState;

	glm::vec2 m_mousePosition;
	glm::vec2 m_mouseMotion;
	glm::vec2 m_mouseWheel;
	
};

typedef Singleton<InputManager> TheInput;

#endif