cmake_minimum_required(VERSION 3.14)

project(csv_parser)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory (applications)
add_subdirectory (libraries)
add_subdirectory (tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)