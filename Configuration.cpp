#include <Configuration.h>

//Constructors
Configuration::Configuration(string interface,
                             FilterType filterType)
    : interface(interface), filterType(filterType)
{
}

//Detector
void Configuration::SetInterface(string& interface)
{
    this->interface = interface;
}

const string& Configuration::GetInterface() const
{
    return this->interface;
}

//Filter
FilterType Configuration::GetFilterType() const
{
    return this->filterType;
}

void Configuration::SetFilterType(FilterType filterType)
{
    this->filterType = filterType;
}

const string& Configuration::GetPcapFilter() const
{
    return pcap_filter[this->filterType];
}
