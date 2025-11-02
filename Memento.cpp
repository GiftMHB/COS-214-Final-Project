// Memento.cpp
#include "Memento.h"
#include "GardenArea.h"
#include "Inventory.h" // Forward declarations in .h; assume headers exist
#include "Staff.h"
#include "Customer.h"
#include "Transaction.h"
#include <ctime> // For time_t

// SystemMemento implementation
SystemMemento::SystemMemento(const std::map<std::string, void*>& state, const std::string& desc)
    : state(state), description(desc) {
    timestamp = std::time(nullptr);
}

std::map<std::string, void*> SystemMemento::getState() const {
    return state;
}

time_t SystemMemento::getTimestamp() const {
    return timestamp;
}

std::string SystemMemento::getDescription() const {
    return description;
}

// SystemOriginator implementation
SystemOriginator::SystemOriginator()
    : gardenArea(nullptr), inventory(nullptr) {} // Initialize pointers; in full system, these would be set

std::map<std::string, void*> SystemOriginator::captureState() {
    std::map<std::string, void*> state;
    // Capture clones or serialized states to avoid direct pointers (deep copy needed for safety)
    // For simplicity, using pointers here; beware: this is shallow and risky for integration
    state["gardenArea"] = gardenArea;
    state["inventory"] = inventory;
    state["staffList"] = &staffList; // Vector address; dangerous, better to clone
    state["customerList"] = &customerList;
    state["transactionHistory"] = &transactionHistory;
    return state;
}

void SystemOriginator::restoreState(const std::map<std::string, void*>& state) {
    // Restore; assumes shallow copy, adjust for deep copy in full system
    if (state.find("gardenArea") != state.end()) gardenArea = static_cast<GardenArea*>(state.at("gardenArea"));
    if (state.find("inventory") != state.end()) inventory = static_cast<Inventory*>(state.at("inventory"));
    // For vectors, this would overwrite pointers; need deep copy logic
    // Placeholder: actual implementation should clone objects
}

SystemMemento* SystemOriginator::createMemento(const std::string& description) {
    return new SystemMemento(captureState(), description);
}

void SystemOriginator::restore(SystemMemento* memento) {
    if (memento) restoreState(memento->getState());
}

std::map<std::string, void*> SystemOriginator::getCurrentState() const {
    return currentState; // Note: currentState not used; perhaps merge with captureState
}

SystemOriginator::~SystemOriginator() {
    // Clean up if owning pointers
}

// MementoCaretaker implementation
MementoCaretaker::MementoCaretaker(int maxSaves) : maxSaves(maxSaves) {}

void MementoCaretaker::saveMemento(SystemMemento* memento) {
    mementos.push_back(memento);
    if (static_cast<int>(mementos.size()) > maxSaves) {
        delete mementos.front();
        mementos.erase(mementos.begin());
    }
}

SystemMemento* MementoCaretaker::getMemento(int index) const {
    if (index >= 0 && index < static_cast<int>(mementos.size())) {
        return mementos[index];
    }
    return nullptr;
}

SystemMemento* MementoCaretaker::getLatestMemento() const {
    if (!mementos.empty()) return mementos.back();
    return nullptr;
}

std::vector<SystemMemento*> MementoCaretaker::getAllMementos() const {
    return mementos;
}

void MementoCaretaker::clearMementos() {
    for (auto m : mementos) delete m;
    mementos.clear();
}

int MementoCaretaker::getNumberOfSaves() const {
    return static_cast<int>(mementos.size());
}

MementoCaretaker::~MementoCaretaker() {
    clearMementos();
}