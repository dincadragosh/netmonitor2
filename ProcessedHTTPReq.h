#ifndef PROCESSEDHTTPREQ_H
#define PROCESSEDHTTPREQ_H

#include <ProcessedPacket.h>

class ProcessedHTTPReq : public ProcessedPacket
{
private:

public:
    vector<string> requested;
    ProcessedHTTPReq(ClientInfo& client,string& host, time_t& time, long int no_pkt = 0);
};


#endif
