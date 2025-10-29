/**
 * @file Subject.h
 * @brief Abstract Subject class for the Observer pattern
 * @details Manages a list of observers and notifies them of state changes
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>
#include <string>
#include <algorithm>

/**
 * @class Subject
 * @brief Abstract subject class that manages observers
 * 
 * This class maintains a list of observers and provides methods to
 * attach, detach, and notify them of changes.
 */
class Subject {
protected:
    std::list<Observer*> observers; ///< List of registered observers

public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Subject() {}

    /**
     * @brief Attach an observer to this subject
     * @param observer Pointer to the observer to attach
     */
    void attach(Observer* observer) {
        if (observer != nullptr && !hasObserver(observer)) {
            observers.push_back(observer);
        }
    }

    /**
     * @brief Detach an observer from this subject
     * @param observer Pointer to the observer to detach
     */
    void detach(Observer* observer) {
        if (observer != nullptr) {
            observers.remove(observer);
        }
    }

    /**
     * @brief Check if an observer is already attached
     * @param observer Pointer to the observer to check
     * @return true if observer is attached, false otherwise
     */
    bool hasObserver(Observer* observer) {
        return std::find(observers.begin(), observers.end(), observer) != observers.end();
    }

    /**
     * @brief Notify all observers of a change
     * @param eventType Type of event that occurred
     */
    void notify(const std::string& eventType) {
        for (std::list<Observer*>::iterator it = observers.begin(); 
             it != observers.end(); ++it) {
            (*it)->update(dynamic_cast<Plant*>(this), eventType);
        }
    }
};

#endif // SUBJECT_H