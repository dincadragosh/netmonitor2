#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Globals.h>

class Configuration
{
private:
    //Detector
    string interface;

    //Filter
    FilterType filterType;
public:
    //Constructors
    Configuration(string iface = "eth0",
                  FilterType filter = FILTER_HTTP_REQUEST);

    //Detector
    void SetInterface(string& interface);
    const string& GetInterface() const;

    //Filter
    FilterType GetFilterType() const;
    void SetFilterType(FilterType filterType);
    const string& GetPcapFilter() const;
};

#endif
