#include "CLI.hpp"
#include "FileSystem.hpp"

int main()
{
    FileSystem vfs;
    CLI cli(vfs);
    cli.run();
    return 0;
}
