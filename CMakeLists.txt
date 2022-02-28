cmake_minimum_required(VERSION 3.20)
project(surl)

set(CMAKE_CXX_STANDARD 17)

add_executable(surl main.cpp)
find_package(leveldb CONFIG REQUIRED)
target_link_libraries(surl PRIVATE leveldb::leveldb)
find_package(log4cplus CONFIG REQUIRED)
target_link_libraries(surl PRIVATE log4cplus::log4cplus)