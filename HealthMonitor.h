/**
 * @file HealthMonitor.h
 * @brief Concrete Observer that monitors plant health
 * @details HealthMonitor observes plants and logs health-related events
 */

#ifndef HEALTH_MONITOR_H
#define HEALTH_MONITOR_H

#include "Observer.h"
#include <string>

/**
 * @class HealthMonitor
 * @brief Concrete observer for monitoring plant health
 * 
 * This observer tracks health changes and alerts when plants
 * need attention due to low health.
 */
class HealthMonitor : public Observer {
private:
    double lastHealthReading; ///< Last recorded health value

public:
    /**
     * @brief Constructor
     */
    HealthMonitor();

    /**
     * @brief Destructor
     */
    ~HealthMonitor();

    /**
     * @brief Update method called when observed plant changes
     * @param subject Pointer to the plant that changed
     * @param eventType Type of event
     */
    void update(Plant* subject, const std::string& eventType);

    /**
     * @brief Get the observer type
     * @return Observer type string "HealthMonitor"
     */
    std::string getObserverType();

    /**
     * @brief Log health data for a plant
     * @param subject Pointer to the plant
     */
    void logHealthData(Plant* subject);
};

#endif // HEALTH_MONITOR_H