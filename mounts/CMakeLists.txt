cmake_minimum_required(VERSION 3.0)

set(LIBRARY_NAME mounts)

message(STATUS "Processing ${LIBRARY_NAME}...")

project(${LIBRARY_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(MOUNTS_INC_DIR "include")
set(MOUNTS_SRC_DIR "src")

file(GLOB_RECURSE MOUNTS_INCLUDE_FILES "${MOUNTS_INC_DIR}/*.h")
file(GLOB_RECURSE MOUNTS_SOURCE_FILES "${MOUNTS_SRC_DIR}/*.cpp")
file(GLOB_RECURSE MOUNTS_PRIVATE_INCLUDE_FILES "${MOUNTS_SRC_DIR}/*.h")

include_directories(${MOUNTS_INC_DIR})

set(MOUNTS_SOURCES ${MOUNTS_INCLUDE_FILES} ${MOUNTS_PRIVATE_INCLUDE_FILES} ${MOUNTS_SOURCE_FILES})

# Unit tests
if(NOT UNITTEST_CPP_FOUND)
	include(../external/unittest-cpp.cmake)
endif()

add_library (${LIBRARY_NAME} ${MOUNTS_SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${MOUNTS_INC_DIR})

target_link_libraries(${LIBRARY_NAME} -ludev -lpthread)

# Unit tests
if(UNITTEST_CPP_FOUND)
	add_subdirectory("tests")
endif()

# demo app
add_subdirectory("tests/demo")

# Doxygen
set(MOUNTS_DOCUMENTATION_DIR "docs")
include(${MOUNTS_DOCUMENTATION_DIR}/doxygen.cmake)

message(STATUS "Processing ${LIBRARY_NAME} done")
