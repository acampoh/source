cmake_minimum_required (VERSION 2.6)
project (Halu)
set (Halu_VERSION_MAJOR 1)
set (Halu_VERSION_MAJOR 0)
#set(CMAKE_CXX_STANDARD 11) # C++11...
#set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
#set(CMAKE_CXX_EXTENSIONS OFF) 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(src/)
file(GLOB SOURCES "src/*.cpp")

add_executable(Halu src/main.cpp ${SOURCES})
