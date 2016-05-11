message(STATUS "Processing mounts demo...")

set(MOUNTSDEMO_SOURCES "main.cpp")

add_executable(mountsDemo ${MOUNTSDEMO_SOURCES})

target_link_libraries (mountsDemo LINK_PUBLIC mounts)

message(STATUS "Processing mounts demo done")

