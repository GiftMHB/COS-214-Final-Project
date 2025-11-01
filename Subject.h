#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>

class Observer;

class Subject {
public:
    virtual ~Subject() = default;
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(const std::string& event) = 0;
};

#endif