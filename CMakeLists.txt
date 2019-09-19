cmake_minimum_required(VERSION 3.14)

project(asyncpq)
set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Library
set(LIBRARY_HEADERS
        include/async_pqxx/operations/exec_functor.hpp
        include/async_pqxx/manager.hpp
        include/async_pqxx/thread_connection.hpp
        )
set(LIBRARY_SOURCES
        src/thread_connection.cpp
        )

add_library(asyncpq STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
target_include_directories(asyncpq PUBLIC include)
target_link_libraries(asyncpq PUBLIC ${CONAN_LIBS})

# Tests
set(TEST_HEADERS)
set(TEST_SOURCES
        test/manager.cpp
        test/precondition_lockfree.cpp
        test/precondition_pqxx.cpp
        test/precondition_thread_local.cpp
        )

add_executable(test_asyncpq test/main.cpp ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(test_asyncpq PRIVATE asyncpq ${CONAN_LIBS})
