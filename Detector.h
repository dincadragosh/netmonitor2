#ifndef DETECTOR_H
#define DETECTOR_H
#include <crafter.h>
#include <Globals.h>
#include <PacketProcessorHTTPReq.h>

using namespace Crafter;

class MonitoringSystem;

class Detector
{
private:
    /* members */
    Sniffer *sniffer;

    MonitoringSystem *master;

    //Processors:
    PacketProcessorHTTPReq processorHTTPreq;

    /* functions */
    // constructors
    Detector(MonitoringSystem& ms);
    ~Detector();

    void StartCapture();

    //Pachet handlers
    static void EthPacketHandler(Packet* packet, void* user); //for the eth device
    static void WlanPacketHandler(Packet* packet, void* user); //for the wi-fi device

public:

    friend class MonitoringSystem;
};

#endif
