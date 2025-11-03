/**
 * @file CommandInvoker.h
 * @brief Declares the CommandInvoker class responsible for executing, undoing, and redoing commands.
 */

#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include "Command.h"
#include <vector>
#include <string>

/**
 * @class CommandInvoker
 * @brief Manages the execution, undoing, and redoing of Command objects.
 *
 * The CommandInvoker class stores a history of executed commands and provides
 * mechanisms to undo and redo actions. It ensures a maximum history size to
 * limit memory usage and maintain performance.
 */
class CommandInvoker {
private:
    /**
     * @brief Stores the history of executed commands.
     */
    std::vector<Command*> commandHistory;

    /**
     * @brief Stores commands that were undone and can be redone.
     */
    std::vector<Command*> undoneCommands;

    /**
     * @brief Maximum number of commands to store in history.
     */
    static const size_t MAX_HISTORY_SIZE = 100;

public:
    /**
     * @brief Destructor that cleans up stored commands if necessary.
     */
    ~CommandInvoker();

    /**
     * @brief Executes a given command and stores it in the command history.
     * @param command Pointer to the Command object to execute.
     * @return A string describing the execution result.
     */
    std::string executeCommand(Command* command);

    /**
     * @brief Undoes the most recently executed command.
     * @return A string describing the result of the undo operation.
     */
    std::string undo();

    /**
     * @brief Redoes the most recently undone command.
     * @return A string describing the result of the redo operation.
     */
    std::string redo();

    /**
     * @brief Retrieves a list of executed command descriptions.
     * @return A vector of strings representing command history.
     */
    std::vector<std::string> getCommandHistory() const;

    /**
     * @brief Clears only the history of executed commands.
     */
    void clearHistory();

    /**
     * @brief Clears both executed and undone command histories.
     */
    void clearAllCommands();

    /**
     * @brief Checks whether an undo operation is possible.
     * @return True if there are commands to undo, otherwise false.
     */
    bool canUndo() const;

    /**
     * @brief Checks whether a redo operation is possible.
     * @return True if there are commands to redo, otherwise false.
     */
    bool canRedo() const;

    /**
     * @brief Retrieves the number of commands currently stored in history.
     * @return The size of the command history.
     */
    size_t getHistorySize() const { return commandHistory.size(); }

    /**
     * @brief Retrieves the number of commands available for redo.
     * @return The size of the redo stack.
     */
    size_t getRedoStackSize() const { return undoneCommands.size(); }
};

#endif
