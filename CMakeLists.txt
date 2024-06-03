# CMakeLists.txt for the Trie Adventure analysis project

# title and scope
project(trieadventure)

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

# executables
add_executable(
  main
  main.cpp trie.hpp
  nodes/utility.hpp nodes/node.hpp nodes/bitmask.hpp nodes/deep.hpp
)

add_executable(
  system_tests
  tests/system_tests.cpp
  trie.hpp nodes/utility.hpp nodes/node.hpp
)

# enable testing
enable_testing()

target_link_libraries(
  system_tests
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(system_tests)