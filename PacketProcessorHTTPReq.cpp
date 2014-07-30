#include <PacketProcessorHTTPReq.h>
#include <ClientInfo.h>
#include <Data.h>
#include <Utils.h>
#include <ProcessedHTTPReq.h>

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
    //client info
    Ethernet *eth = pkt->GetLayer<Ethernet>(1);
    ClientInfo client(eth->GetSourceMAC());
    time_t time;

    //host info
    string payload = pkt->GetLayer<RawLayer>()->GetStringPayload();
    pair<string, string> host = GetHost(payload);

    Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.find(client);
    if (itc == data->processedInfo_HTTPReq.end())
    {

        pair<Data::iteratorClientHTTPReq, bool> p = data->processedInfo_HTTPReq.insert(pair<ClientInfo, map<string, ProcessedHTTPReq*> >(client, map<string, ProcessedHTTPReq*>()));
        itc = p.first;
    }

    Data::iteratorProcessedHTTPReq itp = itc->second.find(host.first);
    if (itp == itc->second.end())
    {
        pair<Data::iteratorProcessedHTTPReq, bool> p = itc->second.insert(pair<string, ProcessedHTTPReq*>(host.first, new ProcessedHTTPReq(client, host.first, time)));
        itp = p.first;
        data->activeProcessedInfo_HTTPReq.push(itp->second);

    }

    itp->second->no_pkt++;
    itp->second->requested.push_back(host.second);

    return true;
}

pair<string, string> PacketProcessorHTTPReq::GetHost(string& payload)
{
        string host, get, aux;
        stringstream payload_stream(payload);
        int found = 0; //1 - host, 2 - get

        while(Utils::SafeGetLine(payload_stream, aux, ' '))
        {
                if (found)
                {
                        if (found == 1)
                        {
                                host = aux;
                                //cout << "host: " << host << endl;
                                found = 0;
                                continue;
                        }
                        else
                        {
                                get = aux;
                                //cout << "GET: " << get <<endl;
                                found = 0;
                                continue;
                        }
                }
                if (aux == "Host:")
                {
                        found = 1;
                }
                else if (aux == "GET")
                {
                        found = 2;
                }

        }

        return pair<string, string>(host, get);
}
