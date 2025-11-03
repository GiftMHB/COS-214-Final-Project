#include "Staff.h"
#include <algorithm>
#include <sstream>

/**
 * @file Staff.cpp
 * @brief Implements the Staff class for managing staff members and their tasks
 * @brief Constructs a Staff object with the given name and role.
 * 
 * @param staffName Name of the staff member.
 * @param staffRole Role or position of the staff member.
 * @throws std::invalid_argument if staffName or staffRole is empty.
 */
Staff::Staff(const std::string& staffName, const std::string& staffRole) 
    : name(staffName), role(staffRole) {
    
    if (staffName.empty()) {
        throw std::invalid_argument("Staff name cannot be empty");
    }
    if (staffRole.empty()) {
        throw std::invalid_argument("Staff role cannot be empty");
    }
}

/**
 * @brief Assigns a new task to the staff member.
 * 
 * @param task The task to assign.
 * @throws std::invalid_argument if the task string is empty.
 */
void Staff::assignTask(const std::string& task) {
    if (task.empty()) {
        throw std::invalid_argument("Task cannot be empty");
    }
    assignedTasks.push_back(task);
}

/**
 * @brief Marks a task as completed and removes it from the assigned tasks list.
 * 
 * @param task The task to complete.
 */
void Staff::completeTask(const std::string& task) {
    auto it = std::find(assignedTasks.begin(), assignedTasks.end(), task);
    if (it != assignedTasks.end()) {
        assignedTasks.erase(it);
    }
}

/**
 * @brief Retrieves all currently assigned tasks for the staff member.
 * 
 * @return A vector of strings representing the assigned tasks.
 */
std::vector<std::string> Staff::getAssignedTasks() const {
    return assignedTasks;
}

/**
 * @brief Provides a formatted string containing staff information and assigned tasks.
 * 
 * @return A string detailing the staff member's name, role, and their assigned tasks.
 */
std::string Staff::getStaffInfo() const {
    std::stringstream ss;
    ss << "Staff: " << name << " (" << role << ")\n";
    ss << "Assigned Tasks: " << assignedTasks.size() << "\n";
    for (const auto& task : assignedTasks) {
        ss << "  - " << task << "\n";
    }
    return ss.str();
}
