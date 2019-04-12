cmake_minimum_required(VERSION 3.02)
project(os_find)

set(CMAKE_CXX_STANDARD 14)

add_executable(os_find
        find.cpp
        ParseUtils.cpp
        ParseUtils.h
        ShellHelper.cpp
        ShellHelper.h
        FindOptions.cpp
        FindOptions.h
)