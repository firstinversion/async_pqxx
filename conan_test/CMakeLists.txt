cmake_minimum_required(VERSION 3.13)

project(test)
set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

# Dependencies

## Executable

add_executable(test main.cpp)
target_link_libraries(test PRIVATE ${CONAN_LIBS})
