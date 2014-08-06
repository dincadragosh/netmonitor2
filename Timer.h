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
    static void GetTime(monitor_time& cur_time);
    static monitor_time GetTime();
    static bool SameTime(monitor_time& first);
    static void StartTime();
};

#endif
