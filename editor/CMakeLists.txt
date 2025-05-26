cmake_minimum_required(VERSION 3.5)
project(counter_strike_2d_editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encuentra Qt5 con todos los módulos necesarios
find_package(Qt5 REQUIRED COMPONENTS Widgets Core)
# Agrega esto después de qt5_wrap_ui
qt5_add_resources(RESOURCES resources/resources.qrc)

# Procesa el archivo UI
qt5_wrap_ui(UI_HEADERS MapEditor.ui)

# Archivos fuente
set(SOURCE_FILES
    main.cpp
    widget.cpp
    ${UI_HEADERS}
)

# Habilita el sistema MOC automático
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${UI_HEADERS} ${RESOURCES})

target_link_libraries(${PROJECT_NAME} 
    Qt5::Widgets 
    Qt5::Core
)

# Asegura que el compilador encuentre los archivos generados
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)