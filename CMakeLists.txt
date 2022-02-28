cmake_minimum_required(VERSION 3.20)
project(surl)

set(CMAKE_CXX_STANDARD 17)
find_path(LOGURU_INCLUDE_DIRS "loguru/loguru.cpp")

add_executable(surl main.cpp ${LOGURU_INCLUDE_DIRS}/loguru/loguru.cpp)
find_package(leveldb CONFIG REQUIRED)
target_link_libraries(surl PRIVATE leveldb::leveldb)
find_path(LOGURU_INCLUDE_DIRS "loguru/loguru.cpp")
target_include_directories(surl PRIVATE ${LOGURU_INCLUDE_DIRS})