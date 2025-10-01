cmake_minimum_required(VERSION 3.16)
project(VirtualFileSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers from include/ folder
include_directories(include)

# Source files
set(SOURCES
    src/File.cpp
    src/Directory.cpp
    src/FileSystem.cpp
    src/CLI.cpp
    src/Utils.cpp
    src/main.cpp
)

add_executable(VirtualFileSystem ${SOURCES})

target_link_libraries(VirtualFileSystem PRIVATE readline)
