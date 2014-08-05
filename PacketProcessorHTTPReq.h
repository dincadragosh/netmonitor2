#ifndef PACKETPROCESSORHTTPREQ_H
#define PACKETPROCESSORHTTPREQ_H

#include <PacketProcessor.h>

class ProcessedHTTPReq;

class PacketProcessorHTTPReq: public PacketProcessor
{
private:
    pair<string, string> GetHost(string& payload);
    bool Store(ProcessedHTTPReq *p);
public:
    PacketProcessorHTTPReq(Data &data);

    bool CanBeProcessed(Packet *pkt);
    bool ProcessPacket(Packet *pkt);
};

#endif
