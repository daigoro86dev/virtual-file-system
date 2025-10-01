#include "CLI.hpp"
#include "FileSystem.hpp"

FileSystem *g_fs_instance = nullptr; // global definition

int main()
{
    FileSystem vfs;
    g_fs_instance = &vfs; // register for completion

    CLI cli(vfs);
    cli.run();
    return 0;
}
