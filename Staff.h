/**
 * @file Staff.h
 * @brief Declares the Staff class representing staff members and their tasks.
 */

#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>

/**
 * @class Staff
 * @brief Represents a staff member, their role, and assigned tasks.
 *
 * The Staff class provides methods to manage tasks assigned to a staff member
 * and retrieve staff information.
 */
class Staff {
private:
    /**
     * @brief Name of the staff member.
     */
    std::string name;

    /**
     * @brief Role or position of the staff member.
     */
    std::string role;

    /**
     * @brief List of tasks assigned to the staff member.
     */
    std::vector<std::string> assignedTasks;

public:
    /**
     * @brief Constructs a Staff object with a given name and role.
     * @param staffName Name of the staff member.
     * @param staffRole Role or position of the staff member.
     */
    Staff(const std::string& staffName, const std::string& staffRole);
    
    /**
     * @brief Retrieves the staff member's name.
     * @return Name of the staff member.
     */
    std::string getName() const { return name; }

    /**
     * @brief Retrieves the staff member's role.
     * @return Role or position of the staff member.
     */
    std::string getRole() const { return role; }

    /**
     * @brief Assigns a new task to the staff member.
     * @param task The task to assign.
     */
    void assignTask(const std::string& task);

    /**
     * @brief Marks a task as completed and removes it from the assigned tasks.
     * @param task The task to complete.
     */
    void completeTask(const std::string& task);

    /**
     * @brief Retrieves all currently assigned tasks.
     * @return Vector of assigned task strings.
     */
    std::vector<std::string> getAssignedTasks() const;

    /**
     * @brief Retrieves a summary of the staff member's information.
     * @return A string containing the name, role, and assigned tasks.
     */
    std::string getStaffInfo() const;
};

#endif
