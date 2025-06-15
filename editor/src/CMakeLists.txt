target_sources(cs2d_editor
    PRIVATE
    main.cpp
    mainwindow.cpp
    sheetdata.cpp
    sheeteditor.cpp
    mapeditor.cpp
    block.cpp
    PUBLIC
    mainwindow.h
    sheetdata.h
    sheeteditor.h
    mapeditor.h
    block.h
)

target_include_directories(cs2d_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})