#ifndef PROCESSEDPACKET_H
#define PROCESSEDPACKET_H

#include <string>
#include <vector>
#include <time.h>

using namespace std;

class ProcessedPacket
{
private:

public:
    ClientInfo client;
    string host;
    long int no_pkt;
    time_t time;

    ProcessedPacket(ClientInfo& client,string host, time_t time, long int no_pkt=0);

};


#endif
