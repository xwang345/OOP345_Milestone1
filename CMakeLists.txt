cmake_minimum_required(VERSION 3.8)
project(Milestone_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        345_ms1_main_prof.cpp
#        Milestone_1.cpp
        Task.cpp
        Task.h
        Utilities.cpp
        Utilities.h)

add_executable(Milestone_1 ${SOURCE_FILES})