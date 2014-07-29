#include <PacketProcessorHTTPReq.h>
#include <ClientInfo.h>
#include <Data.h>
#include <Utils.h>

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

    //host info
    string payload = pkt->GetLayer<RawLayer>()->GetStringPayload();
    pair<string, string> host = GetHost(payload);

    Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.find(client);
    if (itc == data->processedInfo_HTTPReq.end())
    {
        itc = data->processedInfo_HTTPReq.insert(pair<ClientInfo, map<string, ProcessedHTTPReq*> >(client, map<string, ProcessedHTTPReq*>(host.first, 0)));
    }

    Data::iteratorProcessedHTTPReq itp itc->second.find(host.first);
    if (itp == itc->second.end())
    {
        itp = itc->second.insert(map<string, ProcessedHTTPReq*>(host.first, 0)));
    }

    if (itp->second == 0)
    {
        timer_t time;
        itp->second = new ProcessedHTTPReq(client, host, time);
        Data->activeProcessedInfo_HTTPReq.push(itp->second);
    }

    itp->second->no_pkt++;
    itp->second->requested.psuh_back(host.second);

    return true;
}

pair<string, string> PacketProcessorHTTPReq::GetHost(string& payload)
{
        string host, get, aux;
        stringstream payload_stream(payload);
        int found = 0; //1 - host, 2 - get

        while(Utils.SafeGetLine(payload_stream, aux, ' '))
        {
                if (found)
                {
                        if (found == 1)
                        {
                                host = aux;
                                file << "host: " << host << endl;
                                found = 0;
                                continue;
                        }
                        else
                        {
                                get = aux;
                                file << "GET: " << get <<endl;
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
