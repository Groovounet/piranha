#ifndef TIMER_SDL_H
#define TIMER_SDL_H

#include <time.h>

class CTimerSDL 
{
private:
	float m_fStartTime;

public:
	CTimerSDL ();

	void Init ();
	float GetTime () const;
};

#endif //TIMER_SDL_H
