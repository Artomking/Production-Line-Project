cmake_minimum_required(VERSION 3.24)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(FinalProject ms3.cpp Utilities.cpp Utilities.h Station.cpp Station.h CustomerOrder.cpp CustomerOrder.h Workstation.cpp Workstation.h LineManager.cpp LineManager.h)
