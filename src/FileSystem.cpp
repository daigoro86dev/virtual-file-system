#include "FileSystem.hpp"
#include <iostream>
#include <vector>

FileSystem::FileSystem()
{
    root = std::make_shared<Directory>("root", nullptr);
    current = root;
}

void FileSystem::mkdir(const std::string &name)
{
    current->addDirectory(name);
}

void FileSystem::touch(const std::string &name)
{
    current->addFile(name);
}

void FileSystem::ls() const
{
    current->list();
}

void FileSystem::cd(const std::string &name)
{
    if (name == "..")
    {
        if (current->getParent() != nullptr)
        {
            current = std::shared_ptr<Directory>(current->getParent(), [](Directory *) {});
        }
        return;
    }
    auto subdir = current->getSubDirectory(name);
    if (subdir)
    {
        current = subdir;
    }
    else
    {
        std::cout << "Directory not found: " << name << std::endl;
    }
}

void FileSystem::pwd() const
{
    // Build path from current to root
    std::vector<std::string> path;
    Directory *node = current.get();
    while (node != nullptr)
    {
        path.push_back(node->getName());
        node = node->getParent();
    }
    for (auto it = path.rbegin(); it != path.rend(); ++it)
    {
        std::cout << "/" << *it;
    }
    std::cout << std::endl;
}

void FileSystem::tree() const
{
    root->printTree();
}

void FileSystem::cat(const std::string &name) const
{
    auto file = current->getFile(name);
    if (file)
    {
        std::cout << file->getContent() << std::endl;
    }
    else
    {
        std::cout << "File not found: " << name << std::endl;
    }
}

void FileSystem::write(const std::string &name, const std::string &content)
{
    auto file = current->getFile(name);
    if (!file)
    {
        std::cout << "File not found: " << name << std::endl;
        return;
    }
    file->write(content);
}

void FileSystem::cp(const std::string &source, const std::string &destination)
{
    auto srcFile = current->getFile(source);
    if (!srcFile)
    {
        std::cout << "File not found: " << source << std::endl;
        return;
    }

    // Create a new file with destination name and copy content
    current->addFile(destination);
    auto destFile = current->getFile(destination);
    if (destFile)
    {
        destFile->write(srcFile->getContent());
    }
}

void FileSystem::mv(const std::string &source, const std::string &destination)
{
    auto srcFile = current->getFile(source);
    if (!srcFile)
    {
        std::cout << "File not found: " << source << std::endl;
        return;
    }

    // Copy content to new file, then delete old one
    current->addFile(destination);
    auto destFile = current->getFile(destination);
    if (destFile)
    {
        destFile->write(srcFile->getContent());
    }

    // Erase the old file
    current->removeFile(source);
}
