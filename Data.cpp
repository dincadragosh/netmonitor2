#include <Data.h>


Data::Data()
    : processedInfo_HTTPReq(), activeProcessedInfo_HTTPReq(), storeProcessedInfo_HTTPReq()
{
    pthread_mutex_init(&mutex_activeHTTPReq, 0);
    pthread_mutex_init(&mutex_storeHTTPReq, 0);
}

Data::~Data()
{
    pthread_mutex_destroy(&mutex_activeHTTPReq);
    pthread_mutex_destroy(&mutex_storeHTTPReq);
}
