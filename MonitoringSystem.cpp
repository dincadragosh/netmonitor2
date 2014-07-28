#include <MonitoringSystem.h>

MonitoringSystem::MonitoringSystem(Configuration& config)
    : configuration(config), detector(*this)
{
    detector.StartCapture();
}

MonitoringSystem::~MonitoringSystem()
{
}
