cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

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
	./../../src/bitstream.hpp
	./../../src/huffman.hpp
	./../../src/node.hpp
)
set(Sources
	./../../src/bitstream.cpp
	./../../src/huffman.cpp
	./../../src/node.cpp
)

set(ValidAlgTest validAlgTest)

add_executable(${ValidAlgTest} validAlgTest.cpp ${Headers} ${Sources})
target_link_libraries(${ValidAlgTest} PUBLIC ${LibTest})

file(MAKE_DIRECTORY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testTextFiles/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testTextFiles/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testTextFiles/)

add_test(
  NAME ${ValidAlgTest}
  COMMAND ${ValidAlgTest}
)
