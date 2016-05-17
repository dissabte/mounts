message(STATUS "Processing mounts qt demo...")

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE MOUNTS_QT_DEMO_INCLUDE_FILES "*.h")
file(GLOB_RECURSE MOUNTS_QT_DEMO_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE MOUNTS_QT_DEMO_QML_FILES "*.qml")

set(MOUNTS_QT_DEMO_SOURCES ${MOUNTS_QT_DEMO_INCLUDE_FILES} ${MOUNTS_QT_DEMO_SOURCE_FILES})

find_package(Qt5Quick)
find_package(Qt5Widgets)

qt5_add_resources(UI_RESOURCES "main.qrc")

# Adding qml files to the IDE project tree, for convenience
add_custom_target(mountsQtDemoQml SOURCES ${MOUNTS_QT_DEMO_QML_FILES})

# Creating custom target for building qrc, the dependency for main target
add_custom_target(mountsGenerateQRC DEPENDS ${UI_RESOURCES})

add_executable(mountsQtDemo ${MOUNTS_QT_DEMO_SOURCES} ${UI_RESOURCES})

add_dependencies(mountsQtDemo mountsGenerateQRC)

target_link_libraries(mountsQtDemo Qt5::Quick Qt5::Widgets mounts)

message(STATUS "Processing mounts qt demo is done")
