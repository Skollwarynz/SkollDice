cmake_minimum_required(VERSION 3.18.1)
project(SkollDice C)

# Ottimizzazioni e configurazione moduli LVGL
set(LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(LV_USE_THORVG_INTERNAL OFF CACHE BOOL "" FORCE)
set(LV_USE_THORVG_EXTERNAL OFF CACHE BOOL "" FORCE)

# Nome dell'eseguibile
set(PROJECT_EXEC_NAME "SkollDice_bin")

# File sorgente di base
set(SOURCES
    SkollDice/src/main.c
    SkollDice/src/random_dice.c
)

if(ANDROID)
    set(LV_USE_SDL OFF CACHE BOOL "" FORCE)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl/CMakeLists.txt")
        add_subdirectory(SkollDice/dependencies/lvgl)
    endif()

    add_library(${PROJECT_EXEC_NAME} SHARED ${SOURCES})
    target_compile_definitions(${PROJECT_EXEC_NAME} PRIVATE __ANDROID__)
    
    target_include_directories(${PROJECT_EXEC_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/include
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/src
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl
    )

    target_link_libraries(${PROJECT_EXEC_NAME} PRIVATE
        lvgl
        android
        log
        EGL
        GLESv2
    )

elseif(LINUX_APPIMAGE)
    set(LV_USE_SDL ON CACHE BOOL "" FORCE)
    find_package(SDL2 REQUIRED)

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl/CMakeLists.txt")
        include_directories(${SDL2_INCLUDE_DIRS})
        add_subdirectory(SkollDice/dependencies/lvgl)
    endif()

    add_executable(${PROJECT_EXEC_NAME}-linux ${SOURCES})

    target_include_directories(${PROJECT_EXEC_NAME}-linux PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/include
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/src
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl
        ${SDL2_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_EXEC_NAME}-linux PRIVATE
        lvgl
        ${SDL2_LIBRARIES}
    )

else()
    # DESKTOP (Linux / macOS / Windows)
    set(LV_USE_SDL ON CACHE BOOL "" FORCE)
    find_package(SDL2 REQUIRED)

    # Includiamo il file di risorse .rc per Windows per mostrare l'icona sull'eseguibile
    if(WIN32)
        list(APPEND SOURCES SkollDice/Assets/SkollDice.rc)
    endif()

    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl/CMakeLists.txt")
        include_directories(${SDL2_INCLUDE_DIRS})
        add_subdirectory(SkollDice/dependencies/lvgl)
    endif()

    add_executable(${PROJECT_EXEC_NAME} ${SOURCES})

    target_include_directories(${PROJECT_EXEC_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/include
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/src
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/SkollDice/dependencies/lvgl
        ${SDL2_INCLUDE_DIRS}
    )

    if(WIN32)
        target_link_options(${PROJECT_EXEC_NAME} PRIVATE -mconsole)
        target_link_libraries(${PROJECT_EXEC_NAME} PRIVATE
            lvgl
            mingw32
            SDL2main
            SDL2
            m
        )
    else()
        target_link_libraries(${PROJECT_EXEC_NAME} PRIVATE
            lvgl
            ${SDL2_LIBRARIES}
        )
    endif()
endif()
