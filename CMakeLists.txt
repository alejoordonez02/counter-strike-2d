# config de cmake
cmake_minimum_required(VERSION 3.24)
cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON) # extensiones del compilador (gnu, gcc, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # para el linter

# metadata del proyecto
project(
    cs2d
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/alejoordonez02/counter-strike-2d"
    LANGUAGES CXX
)

# activar/ desactivar partes del build
option(CS2D_TESTS "" ON)
option(CS2D_CLIENT "" ON)
option(CS2D_SERVER "" ON)
option(CS2D_EDITOR "" ON)
option(CS2D_MAKE_WARNINGS_AS_ERRORS "" ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")
include(cmake/CompilerWarnings.cmake)

#agregar libraries, los subdirectories de cada una están en los cmake específicos
add_subdirectory(common)
add_subdirectory(server)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
# target_include_directories(cs2d_common PUBLIC .)

# variable DATA_PATH para path de archivos de datos (imágenes, sonidos, etc)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/client")

# HEY!! TODO XXX: you need to install some runtime and dev libraries *before*
# compiling the client/editor code.
#
# In xubuntu 24.04 these are:
#
# sudo apt-get install libopus-dev libopusfile-dev libxmp-dev libfluidsynth-dev fluidsynth libwavpack1 libwavpack-dev libfreetype-dev wavpack
#

# Install libSDL2 and libSDL2pp (for client or editor)
# HEY!! TODO XXX: add more dependendies (either for client, server or editor)
if(CS2D_CLIENT OR CS2D_EDITOR)
    # Use system SDL2 packages
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)
    find_package(yaml-cpp REQUIRED)

    # UI files
    qt5_wrap_ui(UI_HEADERS 
        ${CMAKE_CURRENT_SOURCE_DIR}/editor/src/MapEditor.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/client/ClientInterface.ui
    )
    qt5_add_resources(RESOURCES 
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc
    )

    # Source files
    set(UI_SOURCES
        ${UI_HEADERS}
        ${RESOURCES}
    )

    # Include FetchContent module
    include(FetchContent)
    
    set(SDL2PP_WITH_IMAGE YES)
    # set(SDL2PP_WITH_MIXER YES)
    # set(SDL2PP_WITH_TTF YES)

    # Continue with libSDL2pp
    FetchContent_Declare(
        libSDL2pp
        OVERRIDE_FIND_PACKAGE
        URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )
    
    FetchContent_MakeAvailable(libSDL2pp)
endif()

# Find SDL2 & yaml-cpp packages
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)

# Define static server library for testing
add_library(cs2d_server_lib
    STATIC
    server/model/attack.cpp
    server/model/player.cpp
    server/model/player_physics.cpp
    server/model/random.cpp
    server/model/weapon.cpp
)

target_include_directories(cs2d_server_lib
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/server/model
)

target_link_libraries(cs2d_server_lib
  PUBLIC
    cs2d_common
    yaml-cpp::yaml-cpp
)

# Program section
# ---------------
if(CS2D_CLIENT)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(cs2d_client ${UI_SOURCES})

    # Make them depend on cs2d_common lib
    add_dependencies(cs2d_client cs2d_common SDL2pp::SDL2pp)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(client)

    set_project_warnings(cs2d_client ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)
    set_target_properties(cs2d_client PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
        POSITION_INDEPENDENT_CODE ON
    )

    target_include_directories(cs2d_client PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${yaml-cpp_INCLUDE_DIRS}
    )
    # add libSDL2pp's headers
    target_include_directories(cs2d_client PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the cs2d_common lib target
    target_link_libraries(cs2d_client cs2d_common SDL2pp::SDL2pp Qt5::Widgets Qt5::Core Qt5::Gui yaml-cpp::yaml-cpp)

    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(cs2d_client PRIVATE -fPIC)
    endif()
endif()

if(CS2D_SERVER)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(cs2d_server
      server/main.cpp
    )
    add_dependencies(cs2d_server cs2d_common)
    target_link_libraries(cs2d_server
      PRIVATE
        cs2d_server_lib
    )
endif()

if(CS2D_EDITOR)
    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here

    add_executable(cs2d_editor ${UI_SOURCES})
    add_subdirectory(editor)

    set_target_properties(cs2d_editor PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
        POSITION_INDEPENDENT_CODE ON
    )

    target_include_directories(cs2d_editor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${yaml-cpp_INCLUDE_DIRS}
    )

    target_link_libraries(cs2d_editor Qt5::Widgets Qt5::Core Qt5::Gui yaml-cpp::yaml-cpp
    )

    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(cs2d_editor PRIVATE -fPIC)
    endif()
endif()


# Testing section
# ---------------
if(CS2D_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(cs2d_tests)
    add_dependencies(cs2d_tests cs2d_common)

    add_subdirectory(tests)

    target_include_directories(cs2d_tests
      PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    set_project_warnings(cs2d_tests ${CS2D_MAKE_WARNINGS_AS_ERRORS} TRUE)

    target_link_libraries(cs2d_tests
      PRIVATE
        cs2d_common
        cs2d_server_lib
        yaml-cpp::yaml-cpp
        GTest::gmock_main
    )
endif()
