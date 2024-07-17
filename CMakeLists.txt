# CMakeLists.txt for the Trie Adventure analysis project

cmake_policy(SET CMP0048 NEW)

# title and scope
project(trieadventure VERSION 0.1)

# project requirements
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)

# ensure we can use gdb
set(CMAKE_BUILD_TYPE Debug)

# retrieve the wordlist used by the tests and copy to build directory
file(
  DOWNLOAD http://wiki.puzzlers.org/pub/wordlists/enable1.txt ./dictionary.txt 
  EXPECTED_HASH MD5=33f2b09e2d9dfb732fa16b5f05a5a8d1
)
file(COPY dictionary.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# setup compilation scope and options
include_directories(.)
add_compile_options(-pedantic -Wall -Wextra -Werror=vla -std=c++20)

# testing
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# primary executables
add_executable(
  main
  main.cpp tries/trie.hpp
  nodes/utility.hpp nodes/node.hpp nodes/bitmask.hpp nodes/deep.hpp
)

add_executable(
  statistics
  statistics.cpp tries/statisticstrie.hpp
  nodes/utility.hpp nodes/statistics.hpp
)

# testing executables
add_executable(
  system_tests
  tests/system_tests.cpp
  tries/trie.hpp nodes/utility.hpp nodes/node.hpp
)

add_executable(
  statistics_tests
  tests/statistics_tests.cpp
  tries/statisticstrie.hpp nodes/utility.hpp nodes/statistics.hpp
)

# enable testing
enable_testing()

target_link_libraries(
  system_tests
  GTest::gtest_main
)

target_link_libraries(
  statistics_tests
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(system_tests)
gtest_discover_tests(statistics_tests)