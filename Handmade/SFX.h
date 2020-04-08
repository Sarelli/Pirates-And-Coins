/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a simple sound or sound effect, for example a gun shot, smashing glass,
  cracking wood, etc. The volume of the sound effect can be set with any value between 0 and 128.
  The main member variable is the sound effect pointer, which can be set by requesting the object
  from the Audio Manager. When playing the sound effect, the loop counter can be passed in to tell
  the audio system how many times to loop the sound. By default the sound will only be played once.

*/

#ifndef SFX_H
#define SFX_H

#include <string>
#include <SDL_mixer.h>

class SFX
{

public :

	SFX();

public :

	void SetVolume(int volume);
	void SetSFX(const std::string& mapIndex);

public :

	bool Play(int loop = 0);			
	
private :
	
	Mix_Chunk* m_sfx;
					
};

#endif	