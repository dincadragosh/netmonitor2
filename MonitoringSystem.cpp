#include <MonitoringSystem.h>

MonitoringSystem::MonitoringSystem(Configuration& config)
    : configuration(config), detector(*this), data(), databaseManager(data)
{
    detector.StartCapture();
}

MonitoringSystem::~MonitoringSystem()
{
}
