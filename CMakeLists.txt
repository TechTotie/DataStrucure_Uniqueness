################################################################################
# @file                CMakeLists.txt
# @brief               CMakeFile to compile File Validation Application
# @created             12/12/2019
# @author              Amogh Kudari
################################################################################

cmake_minimum_required(VERSION 2.6)

include_directories(/usr/include)
include_directories(/usr/local/include)

link_directories(/usr/lib)
link_directories(/usr/local/lib)

add_executable(
UniquenessValidator
TestApplication.cpp
)

message(STATUS "COMPILER_OPTION=" ${COMPILER_OPTION})

target_compile_options(UniquenessValidator PUBLIC ${COMPILER_OPTION} "-std=c++17")
