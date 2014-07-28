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
    typedef map<ClientInfo, map<string, ProcessedHTTPReq*> >::iterator iteratorHTTPReq;
    map<ClientInfo, map<string, ProcessedHTTPReq*> > activeProcessedInfo_HTTPReq;
    queue<ProcessedHTTPReq* > saveProcessedInfo_HTTPReq;
};

#endif
