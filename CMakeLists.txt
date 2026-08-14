cmake_minimum_required(VERSION 3.18.1)
project(SkollDice C)

# Ottimizzazioni per disabilitare moduli pesanti/inutili di LVGL
set(LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(LV_USE_THORVG_INTERNAL OFF CACHE BOOL "" FORCE)
set(LV_USE_THORVG_EXTERNAL OFF CACHE BOOL "" FORCE)

set(SOURCES
    src/main.c
    src/random_dice.c
)

if(ANDROID)
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
    # DESKTOP (Linux / macOS / Windows)
    find_package(SDL2 REQUIRED)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/CMakeLists.txt")
        include_directories(${SDL2_INCLUDE_DIRS})
        add_subdirectory(dependencies/lvgl)
    endif()

    add_executable(MiaApp ${SOURCES})

    target_include_directories(MiaApp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl
        ${SDL2_INCLUDE_DIRS}
    )

    if(WIN32)
        target_link_options(MiaApp PRIVATE -mconsole)
        target_link_libraries(MiaApp PRIVATE
            lvgl
            mingw32
            SDL2main
            SDL2
            m
        )
    else()
        target_link_libraries(MiaApp PRIVATE
            lvgl
            ${SDL2_LIBRARIES}
        )
    endif()
endif()
