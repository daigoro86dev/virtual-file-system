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
    std::shared_ptr<Directory> getCurrent() const { return current; }
    void tree() const;
    void cat(const std::string &name) const;
    void write(const std::string &name, const std::string &content);

private:
    std::shared_ptr<Directory> root;
    std::shared_ptr<Directory> current;
};
