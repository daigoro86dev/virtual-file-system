#pragma once
#include <memory>
#include <string>
#include "Directory.hpp"

class FileSystem
{
public:
    FileSystem();

    void mkdir(const std::string &name);
    void touch(const std::string &name);
    void ls() const;
    void cd(const std::string &name);
    void pwd() const;

private:
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> current;
};
