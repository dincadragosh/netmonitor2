#include <Thread.h>
#include <Globals.h>
#include <pthread.h>

pthread_t pthread_collector;
pthread_t pthread_database;

void collectorHandler(void *user)
{
    databaseManager
}

void startThreads()
{
    //start detector/sniffer thread - it calls Detectors handler
    ethMonitor = new MonitoringSystem(ethFactoryConfig);

    /* start database manager */
    databaseManager = new DatabaseManager(ethMonitor.data);

    //start collector thread
    if(pthread_create(&pthread_collector, 0, collectorHandler, 0))
    {
        perror("pthread_create Collector");
        exit(1);
    }

    //start cli thread
}
