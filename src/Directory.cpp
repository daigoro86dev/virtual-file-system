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

void Directory::printTree(const std::string &prefix, bool isLast) const
{
    std::cout << prefix;
    if (!prefix.empty())
    {
        std::cout << (isLast ? "└── " : "├── ");
    }
    std::cout << name << "/" << std::endl;

    // Children (subdirs + files)
    auto totalChildren = subdirectories.size() + files.size();
    size_t counter = 0;

    // Print directories first
    for (const auto &[dname, dptr] : subdirectories)
    {
        counter++;
        bool lastChild = (counter == totalChildren);
        dptr->printTree(prefix + (isLast ? "    " : "│   "), lastChild);
    }

    // Print files
    for (const auto &[fname, fptr] : files)
    {
        counter++;
        bool lastChild = (counter == totalChildren);
        std::cout << prefix << (isLast ? "    " : "│   ")
                  << (lastChild ? "└── " : "├── ")
                  << fname << std::endl;
    }
}
