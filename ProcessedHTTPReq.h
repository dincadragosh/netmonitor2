#ifndef PROCESSEDHTTPREQ_H
#define PROCESSEDHTTPREQ_H

#include <ProcessedPacket.h>

class ProcessedHTTPReq : public ProcessedPacket
{
private:

public:
    vector<string> requested;
    ProcessedHTTPReq(ClientInfo& client,string& host, monitor_time& time, long int no_pkt = 1);
};


#endif
