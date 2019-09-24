cmake_minimum_required(VERSION 3.14)

project(async_pqxx)
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

add_library(async_pqxx STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})
target_include_directories(async_pqxx PUBLIC include)
target_link_libraries(async_pqxx PUBLIC ${CONAN_LIBS})

# Tests
enable_testing()

set(INTEGRATION_TEST_HEADERS)
set(INTEGRATION_TEST_SOURCES
        test/integration/manager.cpp
        )

add_executable(test_integration_async_pqxx test/integration/main.cpp ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(test_integration_async_pqxx PRIVATE async_pqxx ${CONAN_LIBS})
add_test(test_integration ./bin/test_integration_async_pqxx)

set(PRECONDITION_TEST_HEADERS)
set(PRECONDITION_TEST_SOURCES
        test/precondition/precondition_lockfree.cpp
        test/precondition/precondition_pqxx.cpp
        test/precondition/precondition_thread_local.cpp
        )

add_executable(test_precondition_async_pqxx test/precondition/main.cpp ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(test_precondition_async_pqxx PRIVATE async_pqxx ${CONAN_LIBS})
add_test(test_precondition ./bin/test_precondition_async_pqxx)

set(UNIT_TEST_HEADERS)
set(UNIT_TEST_SOURCES)

add_executable(test_unit_async_pqxx test/unit/main.cpp ${TEST_HEADERS} ${TEST_SOURCES})
target_link_libraries(test_unit_async_pqxx PRIVATE async_pqxx ${CONAN_LIBS})
add_test(test_unit ./bin/test_unit_async_pqxx)
