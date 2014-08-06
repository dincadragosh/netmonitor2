#include <Timer.h>

time_t Timer::start_time;

Timer::Timer()
{
}

void Timer::StartTime()
{
    time(&(start_time));
}

bool Timer::SameTime(monitor_time& first)
{
    time_t cur_time;
    time(&cur_time);
    if (difftime(cur_time, first) < UNIT_TIME)
        return true;
    else
        return false;
}

void Timer::GetTime(time_t& cur_time)
{
    time(&cur_time);
}

monitor_time Timer::GetTime()
{
    time_t cur_time;
    time(&cur_time);

    return cur_time;
}
