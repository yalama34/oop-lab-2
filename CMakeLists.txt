cmake_minimum_required(VERSION 3.16)

project(lab-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(string_lib my_string.cpp my_string.h)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests PRIVATE string_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)
