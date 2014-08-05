#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

/* Monitoring systems */
class MonitoringSystem;
extern MonitoringSystem *ethMonitor;
extern MonitoringSystem *wlanMonitor;

/* Config */
class Configuration;
extern Configuration ethFactoryConfig;

//Time:
#define UNIT_TIME 10 //sec
extern time_t time_current;

/* Filter */
enum FilterType
{
    FILTER_HTTP_REQUEST,
    FILTER_ALL
};

extern string pcap_filter[];

/* Debug */
#define DEBUG 1
#define debug_print(_info)    \
            if (DEBUG)  \
                cout << __func__ << "(" << __LINE__ << "):" << _info << endl



#endif
