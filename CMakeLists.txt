cmake_minimum_required(VERSION 3.13)

project(Messaging
    VERSION 0.0.1
    LANGUAGES CXX
)

find_package(MPI REQUIRED COMPONENTS CXX)

add_library(messaging
    src/comm_world.cpp
    src/environment.cpp)

add_library(Messaging ALIAS messaging)

include_directories(messaging PUBLIC include)

target_include_directories(messaging PUBLIC lib/zpp_bits)

target_link_libraries(messaging PUBLIC MPI::MPI_CXX)

if(BUILD_TEST)
    add_subdirectory(test)
endif()