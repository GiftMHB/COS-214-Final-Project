/**
 * @file CommandInvoker.cpp
 * @brief Implements the CommandInvoker class which manages execution, undo, and redo of commands.
 */

#include "CommandInvoker.h"
#include <iostream>

/**
 * @brief Destructor for CommandInvoker.
 *
 * Clears all executed and undone commands to free memory.
 */
CommandInvoker::~CommandInvoker() {
    clearAllCommands();
}

/**
 * @brief Executes a given command and stores it in history.
 * 
 * Clears the redo stack when a new command is executed and ensures
 * the command history does not exceed the maximum size.
 * 
 * @param command Pointer to the command to execute.
 * @return A string indicating the result of the command execution.
 */
std::string CommandInvoker::executeCommand(Command* command) {
    if (command == nullptr) {
        return "Error: Cannot execute null command";
    }
    
    std::string result;
    
    try {
        result = command->execute();
        commandHistory.push_back(command);
        
        // Clear redo stack when new command is executed
        for (Command* cmd : undoneCommands) {
            delete cmd;
        }
        undoneCommands.clear();
        
        // Maintain history size limit
        if (commandHistory.size() > MAX_HISTORY_SIZE) {
            delete commandHistory.front();
            commandHistory.erase(commandHistory.begin());
        }
        
    } catch (const std::exception& e) {
        result = "Command execution failed: " + std::string(e.what());
        delete command;
    }
    
    return result;
}

/**
 * @brief Undoes the most recently executed command.
 * 
 * Moves the undone command to the redo stack.
 * 
 * @return A string describing the result of the undo operation.
 */
std::string CommandInvoker::undo() {
    if (commandHistory.empty()) {
        return "No commands to undo";
    }
    
    Command* cmd = commandHistory.back();
    
    if (!cmd->isUndoable()) {
        return "Cannot undo this command";
    }
    
    std::string result = cmd->undo();
    commandHistory.pop_back();
    undoneCommands.push_back(cmd);
    
    return result;
}

/**
 * @brief Redoes the most recently undone command.
 * 
 * Moves the redone command back to the command history.
 * 
 * @return A string describing the result of the redo operation.
 */
std::string CommandInvoker::redo() {
    if (undoneCommands.empty()) {
        return "No commands to redo";
    }
    
    Command* cmd = undoneCommands.back();
    std::string result = cmd->execute();
    undoneCommands.pop_back();
    commandHistory.push_back(cmd);
    
    return result;
}

/**
 * @brief Retrieves a list of descriptions for all executed commands in history.
 * 
 * @return A vector of strings describing the commands in history.
 */
std::vector<std::string> CommandInvoker::getCommandHistory() const {
    std::vector<std::string> history;
    for (const Command* cmd : commandHistory) {
        history.push_back(cmd->getDescription());
    }
    return history;
}

/**
 * @brief Clears the command history, including executed and undone commands.
 */
void CommandInvoker::clearHistory() {
    clearAllCommands();
}

/**
 * @brief Deletes all commands from both history and redo stacks.
 */
void CommandInvoker::clearAllCommands() {
    for (Command* cmd : commandHistory) {
        delete cmd;
    }
    commandHistory.clear();
    
    for (Command* cmd : undoneCommands) {
        delete cmd;
    }
    undoneCommands.clear();
}

/**
 * @brief Checks whether there are commands available to undo.
 * 
 * @return true if there are commands to undo, false otherwise.
 */
bool CommandInvoker::canUndo() const {
    return !commandHistory.empty();
}

/**
 * @brief Checks whether there are commands available to redo.
 * 
 * @return true if there are commands to redo, false otherwise.
 */
bool CommandInvoker::canRedo() const {
    return !undoneCommands.empty();
}
