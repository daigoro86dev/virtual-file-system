#pragma once
#include <string>
#include <map>
#include <memory>
#include "File.hpp"

class Directory
{
public:
    Directory(const std::string &name, Directory *parent = nullptr);

    const std::string &getName() const;
    void addFile(const std::string &name);
    void addDirectory(const std::string &name);
    std::shared_ptr<Directory> getSubDirectory(const std::string &name);
    std::shared_ptr<File> getFile(const std::string &name);
    void list() const;
    Directory *getParent() const;
    const std::map<std::string, std::shared_ptr<File>> &getFiles() const { return files; }
    const std::map<std::string, std::shared_ptr<Directory>> &getSubDirs() const { return subdirectories; }

private:
    std::string name;
    Directory *parent;
    std::map<std::string, std::shared_ptr<File>> files;
    std::map<std::string, std::shared_ptr<Directory>> subdirectories;
};
