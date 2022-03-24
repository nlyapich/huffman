cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(This Huffman)

project(${This} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

add_compile_options(
	-Werror
	-Wall
	-Wextra
	-O3
)

enable_testing()

set(Headers
	./src/bitstream.hpp
	./src/huffman.hpp
	./src/node.hpp
)
set(Sources
	./src/bitstream.cpp
	./src/huffman.cpp
	./src/node.cpp
)

add_executable(${This} ./src/main.cpp ${Headers} ${Sources})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${This} ${Boost_LIBRARIES})

add_subdirectory(tests)
