/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : February 2017

  -----------------------------------------------------------------------------------------------

- This class encapsulates a music object that is able to play any background song or a voice over
  piece. The volume of the audio can be set with any value between 0 and 128. The main member 
  variable is the music pointer, which can be set by requesting the object from the Audio Manager 
  and stating whether you require a music or voice object. When playing the audio, the loop counter
  can be passed in to tell the audio system whether to play the audio only once or loop it endlessly.

*/

#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <SDL_mixer.h>

class Audio
{

public :

	enum AudioType { MUSIC_AUDIO, VOICE_AUDIO };
	enum LoopType  { PLAY_ONCE = 1, PLAY_ENDLESS = -1 };

public :

	Audio();

public :

	void SetVolume(int volume);
	void SetAudio(const std::string& mapIndex, AudioType audioType);

public :

	bool Play(LoopType loopType = PLAY_ONCE);
	void Pause();
	void Resume();
	void Stop();    			

private :
	
	Mix_Music* m_audio;
					
};

#endif