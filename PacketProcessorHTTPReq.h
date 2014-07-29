#ifndef PACKETPROCESSORHTTPREQ_H
#define PACKETPROCESSORHTTPREQ_H

#include <PacketProcessor.h>

class PacketProcessorHTTPReq: public PacketProcessor
{
private:
    pair<string, string> GetHost(string& payload)
public:
    PacketProcessorHTTPReq(Data &data);

    bool CanBeProcessed(Packet *pkt);
    bool ProcessPacket(Packet *pkt);
};

#endif
