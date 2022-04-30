cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(This Huffman)

project(${This} LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++)

add_compile_options(
	-Werror
	-Wall
	-Wextra
	-O3
)

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
set(GUI
	./src/gui/mainwindow.hpp
	./src/gui/mainwindow.cpp
	./src/gui/mainwindow.ui
)

add_executable(${This} ./src/main.cpp ${Headers} ${Sources} ${GUI})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${This} ${Boost_LIBRARIES})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(${This} Qt5::Widgets)

if (BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()
