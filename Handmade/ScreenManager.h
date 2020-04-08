/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates screen management, and is designed to set up all screen and window 
  related matters. It is there to set up all SDL components that will manage the main game window
  and the canvas it will render to. The SDL renderer is also cleared via this class. The m_width 
  and m_height member variables are separate ints because it looks clearer to identify them 
  separately. This class is a Singleton.

- The Initialize() routine probably does the most work in the class. It is there to set up the SDL
  subsystem, and create a game window and a rendering canvas.   
  
- The Update() and Draw() routines will clear and render the actual game screen respectively, and
  the ShutDown() function closes down the SDL subsystems.  

*/

#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include <string>
#include <glm.hpp>
#include <SDL.h>
#include <SDL_syswm.h>
#include "Singleton.h"

class ScreenManager
{

public:

	friend class Singleton<ScreenManager>;

public :

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	glm::vec2 GetScreenSize();

public :

	void SetClearColor(Uint8 r, Uint8 g, Uint8 b);
	
public:

	bool Initialize(const char* windowTitle, int width = 1024, 
		            int height = 768, bool fullscreen = false);
	
	void Update();
	void Draw();

	void ShutDown();

private:

	ScreenManager();
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);

private :

	int m_width;
	int m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	
};

typedef Singleton<ScreenManager> TheScreen;

#endif