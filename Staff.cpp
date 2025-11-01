#include "Staff.h"
#include <algorithm>
#include <sstream>

Staff::Staff(const std::string& staffName, const std::string& staffRole) 
    : name(staffName), role(staffRole) {
    
    if (staffName.empty()) {
        throw std::invalid_argument("Staff name cannot be empty");
    }
    if (staffRole.empty()) {
        throw std::invalid_argument("Staff role cannot be empty");
    }
}

void Staff::assignTask(const std::string& task) {
    if (task.empty()) {
        throw std::invalid_argument("Task cannot be empty");
    }
    assignedTasks.push_back(task);
}

void Staff::completeTask(const std::string& task) {
    auto it = std::find(assignedTasks.begin(), assignedTasks.end(), task);
    if (it != assignedTasks.end()) {
        assignedTasks.erase(it);
    }
}

std::vector<std::string> Staff::getAssignedTasks() const {
    return assignedTasks;
}

std::string Staff::getStaffInfo() const {
    std::stringstream ss;
    ss << "Staff: " << name << " (" << role << ")\n";
    ss << "Assigned Tasks: " << assignedTasks.size() << "\n";
    for (const auto& task : assignedTasks) {
        ss << "  - " << task << "\n";
    }
    return ss.str();
}