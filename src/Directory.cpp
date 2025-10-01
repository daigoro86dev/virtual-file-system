#include "Directory.hpp"
#include <iostream>

Directory::Directory(const std::string &name, Directory *parent)
    : name(name), parent(parent) {}

const std::string &Directory::getName() const
{
    return name;
}

void Directory::addFile(const std::string &name)
{
    if (files.find(name) == files.end())
    {
        files[name] = std::make_shared<File>(name);
    }
}

void Directory::addDirectory(const std::string &name)
{
    if (subdirectories.find(name) == subdirectories.end())
    {
        subdirectories[name] = std::make_shared<Directory>(name, this);
    }
}

std::shared_ptr<Directory> Directory::getSubDirectory(const std::string &name)
{
    auto it = subdirectories.find(name);
    if (it != subdirectories.end())
    {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<File> Directory::getFile(const std::string &name)
{
    auto it = files.find(name);
    if (it != files.end())
    {
        return it->second;
    }
    return nullptr;
}

void Directory::list() const
{
    for (const auto &[fname, fptr] : files)
    {
        std::cout << fname << " (file)" << std::endl;
    }
    for (const auto &[dname, dptr] : subdirectories)
    {
        std::cout << dname << " (dir)" << std::endl;
    }
}

Directory *Directory::getParent() const
{
    return parent;
}
