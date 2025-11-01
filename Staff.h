#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <vector>

class Staff {
private:
    std::string name;
    std::string role;
    std::vector<std::string> assignedTasks;

public:
    Staff(const std::string& staffName, const std::string& staffRole);
    
    std::string getName() const { return name; }
    std::string getRole() const { return role; }
    void assignTask(const std::string& task);
    void completeTask(const std::string& task);
    std::vector<std::string> getAssignedTasks() const;
    std::string getStaffInfo() const;
};

#endif