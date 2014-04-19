
#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"

class Timer
{
    private:
    int startTicks_;
    bool started_;
    public:
    Timer();
    void start();
    void stop();
    int get_ticks();
    bool is_started();
};

#endif
