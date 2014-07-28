#include <Detector.h>
#include <Configuration.h>
#include <MonitoringSystem.h>
#include <ProcessedHTTPReq.h>

/* non-static functions */
Detector::Detector(MonitoringSystem& ms)
    : master(&ms), processorHTTPreq(ms.data)
{
    //processors initialization

    //sniffer
    this->sniffer = new Sniffer(ms.configuration.GetPcapFilter(), ms.configuration.GetInterface());

//    if (!ms.configuration.GetInterface().compare(0, 3, "eth"))
        this->sniffer->SetPacketHandler(Detector::EthPacketHandler);
//    if (!ms.configuration.GetInterface().compare(0, 4, "wlan"))
//        this->sniffer->SetPacketHandler(Detector::WlanPacketHandler);

    this->StartCapture();
}

Detector::~Detector()
{
    delete this->sniffer;
}

void Detector::StartCapture()
{
    this->sniffer->Spawn(-1);
}

/* static functions */
void Detector::EthPacketHandler(Packet* packet, void* user)
{
    cout << "got packet on eth!" << endl;
//    if(ethMonitor->detector.processorHTTPreq.CanBeProcessed(packet))
//        ethMonitor->detector.processorHTTPreq.ProcessPacket(packet);
}

void Detector::WlanPacketHandler(Packet* packet, void* user)
{
    cout << "got packet on wi-fi!" << endl;
}
