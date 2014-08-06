#ifndef PROCESSEDPACKET_H
#define PROCESSEDPACKET_H

#include <string>
#include <vector>
#include <time.h>
#include <ClientInfo.h>
#include <Globals.h>

using namespace std;

class ProcessedPacket
{
private:

public:
    ClientInfo client;
    string host;
    monitor_time time;
    long int no_pkt;


    ProcessedPacket(ClientInfo& client, string& host, monitor_time& time, long int no_pkt=1);

};


#endif
