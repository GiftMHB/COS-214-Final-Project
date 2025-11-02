/**
 * @file GrowthTracker.h
 * @brief Concrete Observer that tracks plant growth stages
 * @details GrowthTracker observes plants and records growth stage transitions
 */

#ifndef GROWTH_TRACKER_H
#define GROWTH_TRACKER_H

#include "Observer.h"
#include <string>

/**
 * @class GrowthTracker
 * @brief Concrete observer for tracking plant growth
 * 
 * This observer monitors growth stage changes and maintains
 * a record of plant development.
 */
class GrowthTracker : public Observer {
private:
    std::string lastGrowthStage; ///< Last recorded growth stage

public:
    /**
     * @brief Constructor
     */
    GrowthTracker();

    /**
     * @brief Destructor
     */
    ~GrowthTracker();

    /**
     * @brief Update method called when observed plant changes
     * @param subject Pointer to the plant that changed
     * @param eventType Type of event
     */
    void update(Plant* subject, const std::string& eventType);

    /**
     * @brief Get the observer type
     * @return Observer type string "GrowthTracker"
     */
    std::string getObserverType();

    /**
     * @brief Record the current growth stage
     * @param subject Pointer to the plant
     */
    void recordGrowthStage(Plant* subject);
};

#endif // GROWTH_TRACKER_H