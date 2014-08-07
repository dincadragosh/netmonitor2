#include <Timer.h>

time_t Timer::start_time;

Timer::Timer()
{
}

void Timer::StartTime()
{
    time(&(start_time));
}

bool Timer::SameTime(time_t& first)
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

time_t Timer::GetTime()
{
    time_t cur_time;
    time(&cur_time);

    return cur_time;
}

string Timer::PrintTime(time_t& time)
{
    return string(ctime(&time));

}
