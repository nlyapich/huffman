cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

enable_testing()

find_package(GTest QUIET)

if (GTest_FOUND)
  include_directories(${GTEST_INCLUDE_DIRS})

  set(LibTest PUBLIC
    gtest
  	gtest_main
    pthread
  )

  add_subdirectory(validAlgTest)
else ()
  message("Testing not included, because GTest not found")
endif()
