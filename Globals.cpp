#include <Globals.h>
#include <MonitoringSystem.h>
#include <Configuration.h>
#include <Data.h>


/* Global Variables */

/* Monitoring systems */
MonitoringSystem *ethMonitor = 0;
MonitoringSystem *wlanMonitor = 0;

/* Configuration */
Configuration ethFactoryConfig;

 //Time
time_t time_current;

string pcap_filter[] =
{
    /* FILTER_HTTP_REQUEST */ "tcp and dst port 80",
    /* FILTER_ALL */  "tcp and dst port 80"
};


