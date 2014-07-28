#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <Globals.h>
#include <crafter.h>

using namespace Crafter;

class Data;

class PacketProcessor
{
private:

protected:
    FilterType filterType;

    Data& data;

    PacketProcessor(FilterType filterType, Data& data);
    FilterType GetFilterType();

public:

    bool CanBeProcessed(Packet *pkt);
    bool ProcessPacket(Packet *pkt);
};

#endif
