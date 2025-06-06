cmake_minimum_required(VERSION 3.5)
project(counter_strike_2d_editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

find_package(yaml-cpp REQUIRED)

qt5_wrap_ui(UI_HEADERS MapEditor.ui)

qt5_add_resources(RESOURCES resources/resources.qrc)

# Archivos fuente
set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/tilesheetdata.cpp
    src/tilesheeteditor.cpp
    src/mapeditor.cpp
    src/maploader.cpp
    src/block.cpp
    ${UI_HEADERS}
)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UI_HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} 
    Qt5::Widgets 
    Qt5::Gui
    Qt5::Core
    yaml-cpp::yaml-cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${yaml-cpp_INCLUDE_DIRS}
)