#include<PacketProcessorHTTPReq.h>

PacketProcessorHTTPReq::PacketProcessorHTTPReq(Data& data)
    : PacketProcessor(FILTER_HTTP_REQUEST, data)
{
}

bool PacketProcessorHTTPReq::CanBeProcessed(Packet *pkt)
{
    TCP *tcp;
    if (((tcp = pkt->GetLayer<TCP>()) != 0) && tcp->GetDstPort() == 80)
        return true;

    return false;
}

bool PacketProcessorHTTPReq::ProcessPacket(Packet *pkt)
{
    Ethernet *eth = pkt->GetLayer<Ethernet>(1);
    ClientInfo host(eth->GetSourceMAC());

    Data::iteratorHTTPReq = Data->activeProcessedInfo_HTTPReq.find(ClientInfo(host_name));
    if iterator

    return false;
}

pair<string, string> PacketProcessorHTTPReq::GetHost()
{

}
