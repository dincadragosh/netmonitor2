#include <Cli.h>
#include <Globals.h>
#include <Data.h>
#include <MonitoringSystem.h>
#include <ProcessedHTTPReq.h>
#include <Timer.h>

void Cli::ShowMenu(int opt)
{
    switch(opt)
    {
        case 0:
            ShowMainMenu();
            break;
        case 1:
            ShowHTTPReq();
            break;
        case 2:
            ShowStoreHTTPReq();
            break;
        default:
            ShowMainMenu();
    }
}

void Cli::ShowMainMenu()
{
    cout << endl;
    cout << "Main Menu" << endl;
    cout << "---------" << endl;
    cout << "1. Show HTTP Active processed" << endl << endl;
    cout << "2. Show HTTP Store  processed" << endl << endl;
}

void Cli::ShowHTTPReq()
{

    Data *data = &ethMonitor->data;

    pthread_mutex_lock(&data->mutex_activeHTTPReq);

    for(Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.begin(); itc != data->processedInfo_HTTPReq.end(); itc++)
    {
        cout <<"Client " + itc->first.mac_name << endl;
        for(Data::iteratorProcessedHTTPReq itp = itc->second.begin(); itp != itc->second.end(); itp++)
        {
            cout << "\thost: " << itp->first << " no_requests: " << itp->second->no_pkt << " time: " << Timer::PrintTime(itp->second->time) << endl;
        }
    }

    pthread_mutex_unlock(&data->mutex_activeHTTPReq);
}

void Cli::ShowStoreHTTPReq()
{

    Data *data = &ethMonitor->data;

    //pthread_mutex_lock(&data->mutex_storeHTTPReq);

    int size = data->storeProcessedInfo_HTTPReq.size();
    cout << endl << " storeProcessedInfo_HTTPReq numeber of elements: " << size << endl;

    if (size == 0)
        return;

    ProcessedHTTPReq *first = data->storeProcessedInfo_HTTPReq.front();
    data->storeProcessedInfo_HTTPReq.pop();

    //print for firts element
    cout << "Client: " << first->client.mac_name << " host: " << first->host << " no_pkt: " << first->no_pkt << endl;
//        for(vector<string>::iterator is = first->requested.begin(); is != first->requested.end(); is++)
//            cout << "/t" << *is << endl;
    data->storeProcessedInfo_HTTPReq.push(first);

    for(ProcessedHTTPReq *p = data->storeProcessedInfo_HTTPReq.front(); p != first; p = data->storeProcessedInfo_HTTPReq.front())
    {
        cout << "Client: " << p->client.mac_name << " host: " << p->host << " no_pkt: " << p->no_pkt << endl;
//            for(vector<string>::iterator is = p->requested.begin(); is != p->requested.end(); is++)
//                cout << "/t" << *is << endl;
        data->storeProcessedInfo_HTTPReq.pop();
        data->storeProcessedInfo_HTTPReq.push(p);
    }

    //pthread_mutex_unlock(&data->mutex_storeHTTPReq);
}

void Cli::UseCli()
{
    int option;

    ShowMenu(option);
    while(1)
    {
        cin >> option;
        ShowMenu(option);
    }
}
