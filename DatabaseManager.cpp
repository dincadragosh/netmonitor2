#include <DatabaseManager.h>

DatabaseManager::DatabaseManager(Data& data,int no_collectors)
    : data(&data), no_collectors(no_collectors)
{
}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::Collect()
{
    debug_print("Colector started");

    sleep(UNIT_TIME);

    while(1)
    {
        this->CollextHTTPReq();
        sleep(UNIT_TIME / this->no_collectors)
    }
}

void DatabaseManager::CollectHTTPReq()
{
    for(Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.begin(); itc != data->processedInfo_HTTPReq.end(); itc++)
    {
        pthread_mutex_lock(&data->mutex_activeHTTPReq);

        for(Data::iteratorProcessedHTTPReq itp = itc->second.begin(); itp != itc->second.end(); itp++)
            if (!Timer::SameTime(itp->second->time))
            {
                ProcessedHTTPReq* processedForStore = itp->second;

                itc->second.erase(itp);

                pthread_mutex_lock(&data->mutex_storeHTTPReq);
                data->storeProcessedInfo_HTTPReq.push(processedForStore);
                pthread_mutex_unlock(&data->mutex_storeHTTPReq);
            }

        pthread_mutex_unlock(&data->mutex_activeHTTPReq);
    }
}
