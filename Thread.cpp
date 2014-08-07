#include <Thread.h>
#include <Globals.h>
#include <pthread.h>

void startThreads()
{
    //start detector/sniffer thread - it calls Detectors handler
    ethMonitor = new MonitoringSystem(ethFactoryConfig);

    /* start database manager */
    //start collector thread


    //start cli thread
}
