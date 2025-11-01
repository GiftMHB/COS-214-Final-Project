#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include "Command.h"
#include <vector>
#include <string>

class CommandInvoker {
private:
    std::vector<Command*> commandHistory;
    std::vector<Command*> undoneCommands;
    static const size_t MAX_HISTORY_SIZE = 100;

public:
    ~CommandInvoker();
    std::string executeCommand(Command* command);
    std::string undo();
    std::string redo();
    std::vector<std::string> getCommandHistory() const;
    void clearHistory();
    void clearAllCommands();
    bool canUndo() const;
    bool canRedo() const;
    size_t getHistorySize() const { return commandHistory.size(); }
    size_t getRedoStackSize() const { return undoneCommands.size(); }
};

#endif