#ifndef GROWTH_TRACKER_H
#define GROWTH_TRACKER_H

#include "Observer.h"

class GrowthTracker : public Observer {
public:
    virtual void update(Plant* plant);
};

#endif // GROWTH_TRACKER_H
