/**
 * @file Subject.h
 * @brief Declares the Subject interface for implementing the Observer pattern.
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Observer;

/**
 * @class Subject
 * @brief Abstract base class representing a subject in the Observer pattern.
 *
 * The Subject interface allows observers to attach and detach themselves,
 * and provides a mechanism to notify all attached observers about events.
 */
class Subject {
public:
    /**
     * @brief Virtual destructor for safe polymorphic destruction.
     */
    virtual ~Subject() = default;

    /**
     * @brief Attaches an observer to the subject.
     * @param observer Pointer to the Observer to attach.
     */
    virtual void attach(Observer* observer) = 0;

    /**
     * @brief Detaches an observer from the subject.
     * @param observer Pointer to the Observer to detach.
     */
    virtual void detach(Observer* observer) = 0;

    /**
     * @brief Notifies all attached observers of an event.
     * @param event A string describing the event.
     */
    virtual void notify(const std::string& event) = 0;
};

#endif
