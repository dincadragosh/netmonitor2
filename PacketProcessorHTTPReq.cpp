#include <PacketProcessorHTTPReq.h>
#include <ClientInfo.h>
#include <Data.h>
#include <Utils.h>
#include <ProcessedHTTPReq.h>
#include <Timer.h>

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
    bool host_just_added = false;

    //client info
    Ethernet *eth = pkt->GetLayer<Ethernet>();
    if (eth == 0)
        return false;

    ClientInfo client(eth->GetSourceMAC());

    //host info
    RawLayer *rawLayer = pkt->GetLayer<RawLayer>();
    if (rawLayer == 0)
        return false;
    string payload = rawLayer->GetStringPayload();
    pair<string, string> host = GetHost(payload);

    debug_print("client MAC: " + client.mac_name);
    debug_print("host: " + host.first);

    pthread_mutex_lock(&data->mutex_activeHTTPReq);

    Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.find(client);
    if (itc == data->processedInfo_HTTPReq.end())
    {
        debug_print("add as new client");
        pair<Data::iteratorClientHTTPReq, bool> p = data->processedInfo_HTTPReq.insert(pair<ClientInfo, map<string, ProcessedHTTPReq*> >(client, map<string, ProcessedHTTPReq*>()));
        itc = p.first;
    }

    Data::iteratorProcessedHTTPReq itp = itc->second.find(host.first);

    if (itp == itc->second.end())
    {
        debug_print("add new host(" + host.first + ") to mac " + client.mac_name);
        host_just_added = true;
        monitor_time cur_time; Timer::GetTime(&cur_time);
        pair<Data::iteratorProcessedHTTPReq, bool> p = itc->second.insert(pair<string, ProcessedHTTPReq*>(host.first, new ProcessedHTTPReq(client, host.first, cur_time)));
        itp = p.first;
        //data->activeProcessedInfo_HTTPReq.push(itp->second);
    }


    debug_print("number of pkt: " << (itp->second->no_pkt));


    if (host_just_added || Timer::SameTime())
    {
        itp->second->no_pkt++;
        itp->second->requested.push_back(host.second);
    }
    else
    {
        //storing element
        ProcessedHTTPReq* processedForStore = itp->second;

        //itc->second.erase(itp);
        monitor_time cur_time; Timer::GetTime(&cur_time);
        itp->second = new ProcessedHTTPReq(client, host.first, cur_time);

        pthread_mutex_lock(&data->mutex_storeHTTPReq);
        data->storeProcessedInfo_HTTPReq.push(processedForStore);
        pthread_mutex_unlock(&data->mutex_storeHTTPReq);
    }

    pthread_mutex_unlock(&data->mutex_activeHTTPReq);

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

bool PacketProcessorHTTPReq::Store(ProcessedHTTPReq *p)
{
    pthread_mutex_lock(&data->mutex_storeHTTPReq);

    debug_print("Started storing");

    for(ProcessedHTTPReq *front; ; data->activeProcessedInfo_HTTPReq.pop())
    {
        front = data->activeProcessedInfo_HTTPReq.front();
        debug_print("Storing mac:" << front->client.mac_name << " host: " << front->host);

        data->storeProcessedInfo_HTTPReq.push(front);
        if (front == p)
            break;
    }

    pthread_mutex_unlock(&data->mutex_storeHTTPReq);

    return true;
}
