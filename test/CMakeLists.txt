set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# target
add_executable(test test.cpp)
target_link_libraries(test PUBLIC Messaging)