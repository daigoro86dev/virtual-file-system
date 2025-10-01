#include "File.hpp"
#include <chrono>

File::File(const std::string &name)
    : name(name),
      created(std::chrono::system_clock::now()),
      modified(created)
{
}

const std::string &File::getName() const
{
    return name;
}

const std::string &File::getContent() const
{
    return content;
}

void File::write(const std::string &data)
{
    content = data;
    modified = std::chrono::system_clock::now();
}

std::size_t File::getSize() const
{
    return content.size();
}
