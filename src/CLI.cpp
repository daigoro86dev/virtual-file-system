#include "CLI.hpp"
#include <iostream>
#include <sstream>
#include <readline/readline.h>
#include <readline/history.h>
#include <cstring>
#include <vector>

// Forward declaration
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
        char *input = readline("> ");
        if (!input)
            break; // Ctrl+D exits

        std::string cmdline(input);
        free(input);

        if (cmdline == "exit")
            break;

        if (!cmdline.empty())
        {
            add_history(cmdline.c_str());
            handleCommand(cmdline);
        }
    }
}

void CLI::handleCommand(const std::string &input)
{
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;

    if (cmd == "mkdir")
    {
        std::string arg;
        iss >> arg;
        fs.mkdir(arg);
    }
    else if (cmd == "touch")
    {
        std::string arg;
        iss >> arg;
        fs.touch(arg);
    }
    else if (cmd == "ls")
    {
        fs.ls();
    }
    else if (cmd == "cd")
    {
        std::string arg;
        iss >> arg;
        fs.cd(arg);
    }
    else if (cmd == "pwd")
    {
        fs.pwd();
    }
    else if (cmd == "cat")
    {
        std::string arg;
        iss >> arg;
        fs.cat(arg);
    }
    else if (cmd == "write")
    {
        std::string filename;
        iss >> filename;
        std::string content;
        std::getline(iss, content);

        // Strip leading space from getline
        if (!content.empty() && content[0] == ' ')
            content.erase(0, 1);

        fs.write(filename, content);
    }
    else
    {
        std::cout << "Unknown command: " << cmd << std::endl;
    }
}

// --- Completion helpers ---

// Command list
static const char *commands[] = {"mkdir", "touch", "ls", "cd", "pwd", "exit", "tree", "cat", "write", nullptr};

// Generator for command matches
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

// --- File/Directory completion ---
// We’ll use the FileSystem to query current directory contents
extern FileSystem *g_fs_instance; // global pointer hack for readline

char *fileDirGenerator(const char *text, int state)
{
    static std::vector<std::string> matches;
    static size_t index;
    if (!state)
    {
        matches.clear();
        index = 0;

        // Collect files & dirs from current directory
        auto currentDir = g_fs_instance->getCurrent();
        if (currentDir)
        {
            // Add files
            for (const auto &[fname, _] : currentDir->getFiles())
            {
                if (fname.rfind(text, 0) == 0)
                { // starts with text
                    matches.push_back(fname);
                }
            }
            // Add directories
            for (const auto &[dname, _] : currentDir->getSubDirs())
            {
                if (dname.rfind(text, 0) == 0)
                {
                    matches.push_back(dname);
                }
            }
        }
    }

    if (index < matches.size())
    {
        return strdup(matches[index++].c_str());
    }
    return nullptr;
}

// Completion dispatcher
char **cliCompleter(const char *text, int start, int end)
{
    (void)end;

    // At start of line → complete commands
    if (start == 0)
    {
        return rl_completion_matches(text, commandGenerator);
    }
    // Otherwise → complete filenames/directories
    return rl_completion_matches(text, fileDirGenerator);
}
