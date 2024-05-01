cmake_minimum_required(VERSION 3.22.1)
project(ax_test3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ax_test3 main.cpp
        task.cpp
        task.h
        file.cpp
        file.h
        tasks_parser.cpp
        tasks_parser.h
)

target_link_libraries(ax_test3 -lpqxx -lpq)
