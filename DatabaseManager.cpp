#include <DatabaseManager.h>
#include <Globals.h>
#include <Data.h>
#include <Timer.h>
#include <ProcessedHTTPReq.h>
#include <unistd.h>

DatabaseManager::DatabaseManager(Data& data,int no_collectors)
    : data(&data), no_collectors(no_collectors), cond_bool(false)
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
        this->Cond_block();

        this->CollectHTTPReq();

        sleep(UNIT_TIME / this->no_collectors);
        this->Cond_unlock();
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

    while(1)
    {
        this->Cond_lock();

        /* if there aren't any more elements to be stored block thread */
        pthread_mutex_lock(&data->mutex_storeHTTPReq);
        if(data->storeProcessedInfo_HTTPReq.size() == 0)
        {
            this->Cond_block();
            continue;
        }
        pthread_mutex_unlock(&data->mutex_storeHTTPReq);

        //Store an element
    }
}

void DatabaseManager::Cond_lock()
{
    pthread_mutex_lock(&cond_lock);
    while (!cond_bool)
        pthread_cond_wait(&cond_var, &cond_lock);
    //cond_bool = false;
    pthread_mutex_unlock(&cond_lock);
}

void DatabaseManager::Cond_unlock()
{
    pthread_mutex_lock(&cond_lock);
    while (!cond_bool)
        pthread_cond_signal(&cond_var);
    cond_bool = true;
    pthread_mutex_unlock(&cond_lock);
}

void DatabaseManager::Cond_block()
{
    pthread_mutex_lock(&cond_lock);
    cond_bool = false;
    pthread_mutex_unlock(&cond_lock);
}
