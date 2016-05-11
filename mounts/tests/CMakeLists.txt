cmake_minimum_required(VERSION 3.0)

message(STATUS "Processing unittests...")

set(MOUNTS_TESTS mounts_tests)

include_directories(${UNITTEST_CPP_DIR})

file(GLOB MOUNTS_TESTS_INCLUDE_FILES "*.h")
file(GLOB MOUNTS_TESTS_SOURCE_FILES "*.cpp")

set(MOUNTS_TESTS_SOURCES ${MOUNTS_TESTS_INCLUDE_FILES} ${MOUNTS_TESTS_SOURCE_FILES})

add_executable(${MOUNTS_TESTS} ${MOUNTS_TESTS_SOURCES})

add_dependencies(${MOUNTS_TEST} mounts UnitTest++)

target_link_libraries(${MOUNTS_TESTS} mounts UnitTest++)

message(STATUS "Processing unittests done")
