#include <iostream>
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
ScreenManager::ScreenManager()
{

	m_width = 0;
	m_height = 0;

	m_window = nullptr;
	m_renderer = nullptr;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns SDL game window
//------------------------------------------------------------------------------------------------------
SDL_Window* ScreenManager::GetWindow()
{

	return m_window;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns SDL renderer
//------------------------------------------------------------------------------------------------------
SDL_Renderer* ScreenManager::GetRenderer()
{

	return m_renderer;

}
//------------------------------------------------------------------------------------------------------
//getter function that creates screen size vector and returns it
//------------------------------------------------------------------------------------------------------
glm::vec2 ScreenManager::GetScreenSize()
{

	return glm::vec2(m_width, m_height);

}
//------------------------------------------------------------------------------------------------------
//setter function that assigns a pre-defined color value for clearing the screen
//------------------------------------------------------------------------------------------------------
void ScreenManager::SetClearColor(Uint8 r, Uint8 g, Uint8 b)
{

	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);

}
//------------------------------------------------------------------------------------------------------
//function that initializes the screen including the SDL subsystems   
//------------------------------------------------------------------------------------------------------
bool ScreenManager::Initialize(const char* windowTitle, int width, int height, bool fullscreen)
{

	//initialize SDL subsystem by enabling the entire SDL package
	//if SDL initialization fails, display error message and return false
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL did not initialize properly." << std::endl;
		return false;
	}

	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                        width, height, screenFlag);

	//if game window could not be created, display error message and return false
	if (m_window == 0)
	{
		std::cout << "Game window could not be created." << std::endl;
		return false;
	}

	//create SDL renderer using SDL window created earlier
	//we use -1 to use the first capable graphics driver and
	//set the rendering to use the GPU and enable vertical syncing
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | 
		                                          SDL_RENDERER_PRESENTVSYNC);
	
	//if SDL renderer could not be created, display error message and return false
	if (m_renderer == 0)
	{
		std::cout << "Renderer could not be created." << std::endl;
		return false;
	}

	//store width and height properties for later use
	//when returning the width and height to client code
	m_width = width;
	m_height = height;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that clears the rendering canvas
//------------------------------------------------------------------------------------------------------
void ScreenManager::Update()
{

	SDL_RenderClear(m_renderer);

}
//------------------------------------------------------------------------------------------------------
//function that displays the rendering canvas
//------------------------------------------------------------------------------------------------------
void ScreenManager::Draw()
{

	SDL_RenderPresent(m_renderer);

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL and destroys the game window
//------------------------------------------------------------------------------------------------------
void ScreenManager::ShutDown()
{

	//free SDL renderer
	SDL_DestroyRenderer(m_renderer);

	//free game screen and window
	SDL_DestroyWindow(m_window);

	//shut down all SDL sub-systems
	SDL_Quit();

}