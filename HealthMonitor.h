#ifndef HEALTH_MONITOR_H
#define HEALTH_MONITOR_H

#include "Observer.h"

class HealthMonitor : public Observer {
public:
    virtual void update(Plant* plant);
};

#endif // HEALTH_MONITOR_H
