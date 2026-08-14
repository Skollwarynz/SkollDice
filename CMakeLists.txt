cmake_minimum_required(VERSION 3.18.1)
project(SkollDice C)

set(SOURCES
    src/main.c
    src/random_dice.c
)

if(ANDROID)
    # Su Android spegniamo SDL2 per evitare che LVGL cerchi <SDL2/SDL.h>
    set(LV_USE_SDL OFF CACHE BOOL "" FORCE)
    
    # Integriamo LVGL
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
    # Desktop (Linux / macOS / Windows)
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

    find_package(SDL2 REQUIRED)
    target_link_libraries(MiaApp PRIVATE
        lvgl
        ${SDL2_LIBRARIES}
    )
endif()
