#include <pthread.h>
#include <Thread.h>
#include <Globals.h>
#include <DatabaseManager.h>
#include <MonitoringSystem.h>
#include <Cli.h>

pthread_t pthread_collector;
pthread_t pthread_database;

void* collectorHandler(void *user)
{
    databaseManager->Collect();

    return 0;
}

void* databaseHandler(void *user)
{
    databaseManager->Database();

    return 0;
}

void startThreads()
{
    //start detector/sniffer thread - it calls Detectors handler
    ethMonitor = new MonitoringSystem(ethFactoryConfig);

    /* start database manager */
    databaseManager = new DatabaseManager(ethMonitor->data);

    //start collector thread
    if(pthread_create(&pthread_collector, 0, &collectorHandler, 0))
    {
        perror("pthread_create Collector");
        exit(1);
    }

        //start database thread
    if(pthread_create(&pthread_database, 0, &databaseHandler, 0))
    {
        perror("pthread_create Collector");
        exit(1);
    }

    //start cli thread
    Cli::UseCli();
}
