#include <Cli.h>
#include <Globals.h>
#include <Data.h>
#include <MonitoringSystem.h>
#include <ProcessedHTTPReq.h>

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
}

void Cli::ShowHTTPReq()
{

    Data *data = &ethMonitor->data;
    for(Data::iteratorClientHTTPReq itc = data->processedInfo_HTTPReq.begin(); itc != data->processedInfo_HTTPReq.end(); itc++)
    {
        cout <<"Client " + itc->first.mac_name << endl;
        for(Data::iteratorProcessedHTTPReq itp = itc->second.begin(); itp != itc->second.end(); itp++)
        {
            cout << "\thost: " << itp->first << " no_requests: " << itp->second->no_pkt << endl;
        }
    }
}

void Cli::UseCli()
{
    int option;
    while(1)
    {
        cin >> option;
        ShowMenu(option);
    }
}
