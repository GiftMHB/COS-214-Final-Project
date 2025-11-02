/**
 * @file Command.h
 * @brief Defines the abstract Command class for executing and undoing actions on plants.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class Plant;

/**
 * @class Command
 * @brief Abstract base class representing a command that can be executed and undone.
 *
 * The Command class defines a standard interface for implementing the Command design pattern.
 * Derived classes should implement specific actions to be performed on Plant objects or other entities.
 */
class Command {
public:
    /**
     * @brief Virtual destructor for safe polymorphic destruction.
     */
    virtual ~Command() = default;

    /**
     * @brief Executes the command's action.
     * @return A string describing the result or status of the execution.
     */
    virtual std::string execute() = 0;

    /**
     * @brief Undoes the previously executed command's action.
     * @return A string describing the result or status of the undo operation.
     */
    virtual std::string undo() = 0;

    /**
     * @brief Provides a human-readable description of the command.
     * @return A string describing what the command does.
     */
    virtual std::string getDescription() const = 0;

    /**
     * @brief Retrieves the type or category of the command.
     * @return A string identifying the command type.
     */
    virtual std::string getCommandType() const = 0;

    /**
     * @brief Indicates whether the command supports undo functionality.
     * @return True if the command can be undone, otherwise false.
     */
    virtual bool isUndoable() const { return true; }
};

#endif
