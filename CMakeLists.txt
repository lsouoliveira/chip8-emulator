cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(chip8_emulator)

enable_testing()

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(LIBS -lfmt)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} ${LIBS})

add_library(${PROJECT_NAME}_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_subdirectory(test)