
#include "timer.h"

Timer::Timer()
{
  startTicks_ = 0;
  started_ = false;
}

void Timer::start()
{
  started_ = true;
  startTicks_ = SDL_GetTicks();
}

void Timer::stop()
{
  started_ = false;
}

int Timer::get_ticks()
{
  if (started_)
  {
    return SDL_GetTicks() - startTicks_;
  }
  else return 0;
}

bool Timer::is_started()
{
  return started_;
}
