#include <DatabaseManager.h>
#include <Globals.h>
#include <Data.h>
#include <Timer.h>
#include <ProcessedHTTPReq.h>
#include <unistd.h>

DatabaseManager::DatabaseManager(Data& data,int no_collectors)
    : data(&data), no_collectors(no_collectors), cond_bool(false)
{
    pthread_mutex_init(&this->cond_lock, 0);
    pthread_cond_init(&this->cond_var, 0);
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
        debug_print("Collector - block Database");
        this->Cond_block();
        debug_print("Collector - start collecting");

        this->CollectHTTPReq();

        debug_print("Collector - finished collecting");
        this->Cond_unlock();
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
                debug_print("Collector - collecting " << itp->second->host);
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

    if (!this->sqlite.OpenDatabase())
    {
        debug_print("SQLiteInterface failed to open database ");
        return;
    }

    sleep(UNIT_TIME);

    while(1)
    {
        debug_print("Database - waiting to store");
        this->Cond_lock();
        debug_print("Database - started storing");

        /* if there aren't any more elements to be stored block thread */
        pthread_mutex_lock(&data->mutex_storeHTTPReq);
        if(data->storeProcessedInfo_HTTPReq.size() == 0)
        {
            debug_print("Database - no more elements to store, so blocking");
            this->Cond_block();
        }
        else
        {
            ProcessedHTTPReq *info = data->storeProcessedInfo_HTTPReq.front();
            debug_print("Database - started storing " << info->host);

            this->sqlite.InsertHistory(info);
            data->storeProcessedInfo_HTTPReq.pop();
            delete info;

            debug_print("Database - finished storing the element");
        }
        pthread_mutex_unlock(&data->mutex_storeHTTPReq);
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
    if (!cond_bool)
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
