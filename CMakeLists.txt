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
add_executable(adventure main.cpp trie.h trie.cpp)