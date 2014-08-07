#ifndef MONITORINGSYSTEM_H
#define MONITORINGSYSTEM_H

#include <Configuration.h>
#include <Detector.h>
#include <Data.h>
#include <DatabaseManager.h>

class MonitoringSystem
{
private:

public:
    Configuration configuration;
    Detector detector;
    Data data;
    DatabaseManager databaseManager;

    MonitoringSystem(Configuration &configuration);
    ~MonitoringSystem();
};

#endif
