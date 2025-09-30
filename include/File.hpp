#pragma once
#include <string>
#include <chrono>

class File
{
public:
    File(const std::string &name);

    const std::string &getName() const;
    const std::string &getContent() const;
    void write(const std::string &data);
    std::size_t getSize() const;

private:
    std::string name;
    std::string content;
    std::chrono::system_clock::time_point created;
    std::chrono::system_clock::time_point modified;
};
