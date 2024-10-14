add_executable(${CMAKE_PROJECT_NAME}
	shell.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
