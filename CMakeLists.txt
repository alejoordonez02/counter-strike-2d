cmake_minimum_required(VERSION 3.24)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cs2d
    VERSION 1.0
    HOMEPAGE_URL "https://github.com/alejoordonez02/counter-strike-2d"
    LANGUAGES CXX
    )

option(CS2D_TESTS "Enable / disable tests." ON)
option(CS2D_CLIENT "Enable / disable client program." ON)
option(CS2D_SERVER "Enable / disable server program." ON)
option(CS2D_EDITOR "Enable / disable editor program." ON)
option(CS2D_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
# HEY TODO XXX: change the name to something that you like
add_library(cs2d_common STATIC)

# add the source files that make the lib
# HEY!! TODO XXX: add more subfolders here
add_subdirectory(common/)


# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(cs2d_common ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(cs2d_common PUBLIC .)

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

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Program section
# ---------------
if(CS2D_CLIENT)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(cs2d_client)

    # Make them depend on cs2d_common lib
    add_dependencies(cs2d_client cs2d_common SDL2pp::SDL2pp)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(client)

    set_project_warnings(cs2d_client ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(cs2d_client PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the cs2d_common lib target
    target_link_libraries(cs2d_client cs2d_common SDL2pp::SDL2pp)
endif()

if(CS2D_SERVER)
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(cs2d_server)

    # Make them depend on cs2d_common lib
    add_dependencies(cs2d_server cs2d_common)

    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(server)
    add_subdirectory(server/model)

    set_project_warnings(cs2d_server ${CS2D_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the cs2d_common lib target
    target_link_libraries(cs2d_server PRIVATE cs2d_common cs2d_server_model)
endif()

if(CS2D_EDITOR)
    # Add source files and enable warnings
    # HEY!! TODO XXX: add more subfolders here

    cmake_minimum_required(VERSION 3.5)
    project(cs2d_editor)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets Core Gui)
    find_package(yaml-cpp REQUIRED)

    qt5_wrap_ui(UI_HEADERS editor/MapEditor.ui)
    qt5_add_resources(RESOURCES resources/resources.qrc)

    # Archivos fuente
    set(SOURCE_FILES
        editor/src/main.cpp
        editor/src/mainwindow.cpp
        editor/src/sheetdata.cpp
        editor/src/sheeteditor.cpp
        editor/src/mapeditor.cpp
        editor/src/maploader.cpp
        editor/src/block.cpp
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

endif()


# Testing section
# ---------------

if(CS2D_TESTS)
    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    # target for testing
    # HEY!! TODO XXX: Change the name of the executable to the one you like!
    add_executable(cs2d_tests)

    # HEY!! TODO XXX: I'm assuming that the code under testing is in cs2d_common
    # Change this if you have to.
    add_dependencies(cs2d_tests cs2d_common)

    # Say where to find the xoz headers
    # HEY!! TODO XXX: add more subfolders here
    target_include_directories(cs2d_tests PUBLIC .)

    # Add the source files to the cs2d_tests target
    # HEY!! TODO XXX: add more subfolders here
    add_subdirectory(tests/)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(cs2d_tests ${CS2D_MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Link the cs2d_tests lib target
    target_link_libraries(cs2d_tests
        PRIVATE # Use PRIVATE if these libs are only for the tests, PUBLIC if cs2d_tests was a library itself
        cs2d_common
        cs2d_server_model
        GTest::gmock_main # This includes gmock and gtest and provides a main function
        # If you have your own main() in tests, you would use:
        # GTest::gmock
        # GTest::gtest
    )
endif()
