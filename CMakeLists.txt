cmake_minimum_required(VERSION 3.0)
project(snake_labyrinth)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(snake main.c snake.c)

target_include_directories(snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -pedantic-errors -Wall -Wextra -O0 -Wno-unused-result -g")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c99 -pedantic-errors -Wall -Wextra -O3 -Wno-unused-result")
