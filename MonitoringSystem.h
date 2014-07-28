#ifndef MONITORINGSYSTEM_H
#define MONITORINGSYSTEM_H

#include <Configuration.h>
#include <Detector.h>
#include <Data.h>

class MonitoringSystem
{
private:

public:
    Configuration configuration;
    Detector detector;
    Data data;

    MonitoringSystem(Configuration &configuration);
    ~MonitoringSystem();
};

#endif
