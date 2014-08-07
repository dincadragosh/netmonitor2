#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <pthread.h>
#include <Globals.h>


class Timer
{
private:
    Timer();

    static time_t start_time;

//    static pthread_t pthread_timer;
//    static pthread_mutex_t mutex_timer;
//    static void SetCurUnit();

public:
    static void GetTime(time_t& cur_time);
    static time_t GetTime();
    static bool SameTime(time_t& first);
    static void StartTime();
    static string PrintTime(time_t& time);
};

#endif
