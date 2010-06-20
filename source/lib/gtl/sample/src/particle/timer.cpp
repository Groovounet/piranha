#include "./timer.h"
#include "./window_sdl.h"

CTimerSDL::CTimerSDL ()
{

}

// Initialisation du timer
void CTimerSDL::Init ()
{
	m_fStartTime = SDL_GetTicks () / 1000.f;
}

// Retourne le temps ecoul� depuis la derni�re initialisation
float CTimerSDL::GetTime () const
{
	return (static_cast<float> (SDL_GetTicks () / 1000.f - m_fStartTime));
}
