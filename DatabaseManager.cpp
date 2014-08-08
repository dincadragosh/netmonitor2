#include <DatabaseManager.h>
#include <Globals.h>
#include <Data.h>
#include <Timer.h>
#include <ProcessedHTTPReq.h>

DatabaseManager::DatabaseManager(Data& data,int no_collectors)
    : data(&data), no_collectors(no_collectors)
{
}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::Collect()
{
    debug_print("Colector thread started");

    sleep(UNIT_TIME);

    while(1)
    {
        this->CollectHTTPReq();
        sleep(UNIT_TIME / this->no_collectors);
    }
}

void DatabaseManager::CollectHTTPReq()
{
    for(Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.begin(); itc != data->processedInfo_HTTPReq.end(); itc++)
    {
        pthread_mutex_lock(&data->mutex_activeHTTPReq);

        for(Data::iteratorProcessedHTTPReq itp = itc->second.begin(); itp != itc->second.end(); )
            if (!Timer::SameTime(itp->second->time))
            {
                ProcessedHTTPReq* processedForStore = itp->second;

                itc->second.erase(itp++);

                pthread_mutex_lock(&data->mutex_storeHTTPReq);
                data->storeProcessedInfo_HTTPReq.push(processedForStore);
                pthread_mutex_unlock(&data->mutex_storeHTTPReq);
            }
            else
            {
                ++itp;
            }

        pthread_mutex_unlock(&data->mutex_activeHTTPReq);
    }
}

void DatabaseManager::Database()
{
    debug_print("Database thread started");


}



void cond_lock() {
    pthread_mutex_lock(&cond_lock);
    while (!cond_bool)
        pthread_cond_wait(&cond_var, &cond_lock);
    cond_bool = false;
    pthread_mutex_unlock(&cond_lock);
}

void cond_unlock() {
    pthread_mutex_lock(&cond_lock);
    while (cond_bool)
        pthread_cond_signal(&cond_var);
    cond_bool = false;
    pthread_mutex_unlock(&cond_lock);
}
