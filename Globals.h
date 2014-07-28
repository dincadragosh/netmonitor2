#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Monitoring systems */
class MonitoringSystem;
extern MonitoringSystem *ethMonitor;
extern MonitoringSystem *wlanMonitor;

/* Config */
class Configuration;
extern Configuration ethFactoryConfig;

//Time:
#define UNIT_TIME 60 //sec
extern time_t time_current;

/* Filter */
enum FilterType
{
    FILTER_HTTP_REQUEST,
    FILTER_ALL
};

extern string pcap_filter[];

#endif
