#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class Plant;

class Command {
public:
    virtual ~Command() = default;
    virtual std::string execute() = 0;
    virtual std::string undo() = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getCommandType() const = 0;
    virtual bool isUndoable() const { return true; }
};

#endif