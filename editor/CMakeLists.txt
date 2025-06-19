target_sources(cs2d_editor
    PRIVATE
    block.cpp
    main.cpp
    main_window.cpp
    map_editor.cpp
    map_editor.ui
    sheet_data.cpp
    sheet_editor.cpp
)

target_include_directories(cs2d_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
