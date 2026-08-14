cmake_minimum_required(VERSION 3.18.1)
project(SkollDice C)

set(SOURCES
    src/main.c
    src/random_dice.c
)

if(ANDROID)
    # Disabilita il driver SDL di LVGL su Android
    set(LV_USE_SDL OFF CACHE BOOL "" FORCE)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/CMakeLists.txt")
        add_subdirectory(dependencies/lvgl)
    endif()

    add_library(main SHARED ${SOURCES})
    target_compile_definitions(main PRIVATE __ANDROID__)
    
    target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl
    )

    target_link_libraries(main PRIVATE
        lvgl
        android
        log
        EGL
        GLESv2
    )
else()
    # CONFIGURAZIONE DESKTOP (Linux / macOS / Windows)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/CMakeLists.txt")
        add_subdirectory(dependencies/lvgl)
    endif()

    add_executable(MiaApp ${SOURCES})

    target_include_directories(MiaApp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl
    )

    if(WIN32)
        # Su Windows diciamogli di usare il classico main() anziché WinMain
        target_link_options(MiaApp PRIVATE -mconsole)
        
        find_library(SDL2_LIB NAMES SDL2)
        find_library(SDL2MAIN_LIB NAMES SDL2main)
        target_link_libraries(MiaApp PRIVATE
            lvgl
            ${SDL2MAIN_LIB}
            ${SDL2_LIB}
            mingw32
            m
        )
    else()
        find_package(SDL2 REQUIRED)
        target_link_libraries(MiaApp PRIVATE
            lvgl
            ${SDL2_LIBRARIES}
        )
    endif()
endif()
