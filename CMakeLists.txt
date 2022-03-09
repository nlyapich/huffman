cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(This Huffman)

project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

add_compile_options(
	-Werror
	-Wall
	-O3
)

set(Headers
	bitstream.hpp
	huffman.hpp
	node.hpp
)
set(Sources
	bitstream.cpp
	huffman.cpp
	node.cpp
)

add_executable(${This} main.cpp ${Sources} ${Headers})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${This} ${Boost_LIBRARIES})
