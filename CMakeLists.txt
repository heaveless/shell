cmake_minimum_required(VERSION 3.27)

project(shell)

add_executable(${CMAKE_PROJECT_NAME}
	src/shell.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
