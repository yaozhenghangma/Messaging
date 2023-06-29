cmake_minimum_required(VERSION 3.13)

project(Messaging
    VERSION 0.1.0
    LANGUAGES CXX
)

# The minimum C++ standard for this library is C++20.
if(NOT DEFINED CMAKE_CXX_STANDARD)
    message(WARNING "No C++ standard was set. A safe C++ standard of C++20 is set.")
    set(CMAKE_CXX_STANDARD 20)
elseif (${CMAKE_CXX_STANDARD} LESS 20)
    message(FATAL_ERROR "The minimum C++ standard is c++20.")
endif()

# Find MPI include path and lib path.
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