#ifndef OBSERVER_H
#define OBSERVER_H

class Plant; // Forward declaration

class Observer {
public:
    virtual ~Observer() {}
    virtual void update(Plant* Plant) = 0;
};

#endif // OBSERVER_H
