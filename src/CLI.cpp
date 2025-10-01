#include "CLI.hpp"
#include <iostream>
#include <sstream>
#include <readline/readline.h>
#include <readline/history.h>

// Forward declaration of the completion function
char **cliCompleter(const char *text, int start, int end);

CLI::CLI(FileSystem &fs) : fs(fs)
{
    // Register the completion function
    rl_attempted_completion_function = cliCompleter;
}

void CLI::run()
{
    while (true)
    {
        // readline allocates memory for the input
        char *input = readline("> ");
        if (!input)
            break; // Ctrl+D exits

        std::string cmdline(input);
        free(input); // free memory from readline

        if (cmdline == "exit")
            break;

        if (!cmdline.empty())
        {
            add_history(cmdline.c_str()); // save to history
            handleCommand(cmdline);
        }
    }
}

void CLI::handleCommand(const std::string &input)
{
    std::istringstream iss(input);
    std::string cmd, arg;
    iss >> cmd;
    iss >> arg;

    if (cmd == "mkdir")
    {
        fs.mkdir(arg);
    }
    else if (cmd == "touch")
    {
        fs.touch(arg);
    }
    else if (cmd == "ls")
    {
        fs.ls();
    }
    else if (cmd == "cd")
    {
        fs.cd(arg);
    }
    else if (cmd == "pwd")
    {
        fs.pwd();
    }
    else
    {
        std::cout << "Unknown command: " << cmd << std::endl;
    }
}

// --- Completion setup ---
// List of supported commands
static const char *commands[] = {"mkdir", "touch", "ls", "cd", "pwd", "exit", nullptr};

// Generator for readline matches
char *commandGenerator(const char *text, int state)
{
    static int listIndex, len;
    if (!state)
    {
        listIndex = 0;
        len = strlen(text);
    }
    while (commands[listIndex])
    {
        const char *name = commands[listIndex];
        listIndex++;
        if (strncmp(name, text, len) == 0)
        {
            return strdup(name);
        }
    }
    return nullptr;
}

// Hook function for readline
char **cliCompleter(const char *text, int start, int end)
{
    (void)end; // unused
    // If at the start of the line, complete commands
    if (start == 0)
    {
        return rl_completion_matches(text, commandGenerator);
    }
    // In the future, we could add file/directory completion here
    return nullptr;
}
