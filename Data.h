#ifndef DATA_H
#define DATA_H

#include <map>
#include <queue>
#include <pthread.h>
#include <ClientInfo.h>

class ProcessedHTTPReq;

class Data
{
private:

public:
    Data();
    ~Data();
    //HTTP Requests
    typedef map<ClientInfo, map<string, ProcessedHTTPReq*> >::iterator iteratorClientHTTPReq;
    typedef map<string, ProcessedHTTPReq*>::iterator iteratorProcessedHTTPReq;
    pthread_mutex_t mutex_activeHTTPReq, mutex_storeHTTPReq;
    map<ClientInfo, map<string, ProcessedHTTPReq*> > processedInfo_HTTPReq;
    queue<ProcessedHTTPReq* > activeProcessedInfo_HTTPReq;
    queue<ProcessedHTTPReq* > storeProcessedInfo_HTTPReq;
};

#endif
