#include "CLI.hpp"
#include <iostream>
#include <sstream>

CLI::CLI(FileSystem &fs) : fs(fs) {}

void CLI::run()
{
    std::string input;
    while (true)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, input))
            break;
        if (input == "exit")
            break;
        handleCommand(input);
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
