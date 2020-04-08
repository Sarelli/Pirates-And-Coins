/*

  All engine code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

*/

/*
    Last game update: 08/04/2020

    CREDITS:
    Game Developer: Sara Viele
    Animation Artist: Roberto Faraone
    Music Composer: Shane Ivers

*/

//include SDL main header file to prevent 
//main lib conflicts in Release mode
#include <SDL.h>
#include <iostream>
#include <string>

#include "Character.h"
#include "GameManager.h"

int main(int argc, char* args[])
{
    TheGame::Instance()->Initialisation();
    TheGame::Instance()->Gameplay();
    TheGame::Instance()->Shutdown();

	return 0;

}