cmake_minimum_required(VERSION 3.11.0)
project(ldp-intermedio VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(source_dir "${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE src_files "${source_dir}/*.cpp")

message(STATUS "Source Dir: ${source_dir}")
message(STATUS "Files: ${src_files}")

add_executable(${PROJECT_NAME} ${src_files})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
	include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Wpedantic")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")


