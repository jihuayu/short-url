cmake_minimum_required(VERSION 3.20)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp)
find_package(leveldb CONFIG REQUIRED)
target_link_libraries(untitled1 PRIVATE leveldb::leveldb)
find_package(log4cplus CONFIG REQUIRED)
target_link_libraries(untitled1 PRIVATE log4cplus::log4cplus)