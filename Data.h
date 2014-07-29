#ifndef DATA_H
#define DATA_H

#include <map>
#include <queue>
#include <ClientInfo.h>

class ProcessedHTTPReq;

class Data
{
private:

public:
    //HTTP Requests
    typedef map<ClientInfo, map<string, ProcessedHTTPReq*> >::iterator iteratorClientHTTPReq;
    typedef map<string, ProcessedHTTPReq*>::iterator iteratorProcessedHTTPReq;
    map<ClientInfo, map<string, ProcessedHTTPReq*> > processedInfo_HTTPReq;
    queue<ProcessedHTTPReq* > activeProcessedInfo_HTTPReq;
    queue<ProcessedHTTPReq* > saveProcessedInfo_HTTPReq;
};

#endif
