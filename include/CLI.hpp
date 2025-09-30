#pragma once
#include <string>
#include "FileSystem.hpp"

class CLI
{
public:
    CLI(FileSystem &fs);
    void run();

private:
    FileSystem &fs;
    void handleCommand(const std::string &input);
};
