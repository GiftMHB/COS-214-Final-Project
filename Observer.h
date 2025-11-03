/**
 * @file Observer.h
 * @brief Abstract Observer interface for the Observer design pattern
 * @details Defines the interface for objects that should be notified of changes
 *          in subject objects (plants).
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

// Forward declaration
class Plant;

/**
 * @class Observer
 * @brief Abstract observer interface
 * 
 * This class defines the interface that concrete observers must implement
 * to receive updates from subject objects.
 */
class Observer {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Observer() {}

    /**
     * @brief Update method called when subject changes
     * @param subject Pointer to the plant that changed
     * @param eventType Type of event that occurred (e.g., "watered", "fertilized", "health_low")
     */
    virtual void update(Plant* subject, const std::string& eventType) = 0;

    /**
     * @brief Get the type of this observer
     * @return Observer type as string
     */
    virtual std::string getObserverType() = 0;
};

#endif // OBSERVER_H