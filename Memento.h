#ifndef MEMENTO_H
#define MEMENTO_H

#include <map>
#include <string>
#include <vector>
#include <ctime>

// Forward declarations
class GardenArea;
class Inventory;
class Staff;
class Customer;
class Transaction;

// Memento class - stores system state
class SystemMemento {
private:
    std::map<std::string, void*> state;
    time_t timestamp;
    std::string description;

public:
    SystemMemento(const std::map<std::string, void*>& state, const std::string& desc);
    
    std::map<std::string, void*> getState() const;
    time_t getTimestamp() const;
    std::string getDescription() const;
};

// Originator - creates and restores mementos
class SystemOriginator {
private:
    std::map<std::string, void*> currentState;
    GardenArea* gardenArea;
    Inventory* inventory;
    std::vector<Staff*> staffList;
    std::vector<Customer*> customerList;
    std::vector<Transaction*> transactionHistory;
    
    std::map<std::string, void*> captureState();
    void restoreState(const std::map<std::string, void*>& state);

public:
    SystemOriginator();
    
    SystemMemento* createMemento(const std::string& description);
    void restore(SystemMemento* memento);
    std::map<std::string, void*> getCurrentState() const;
    
    ~SystemOriginator();
};

// Caretaker - manages mementos
class MementoCaretaker {
private:
    std::vector<SystemMemento*> mementos;
    int maxSaves;

public:
    MementoCaretaker(int maxSaves = 10);
    
    void saveMemento(SystemMemento* memento);
    SystemMemento* getMemento(int index) const;
    SystemMemento* getLatestMemento() const;
    std::vector<SystemMemento*> getAllMementos() const;
    void clearMementos();
    int getNumberOfSaves() const;
    
    ~MementoCaretaker();
};

#endif // MEMENTO_H