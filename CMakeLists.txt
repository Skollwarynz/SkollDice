cmake_minimum_required(VERSION 3.18.1)
project(SkollDice C)

# 1. Trova i file sorgente reali del tuo progetto
set(SOURCES
    src/main.c
    src/random_dice.c
)

# 2. Includi la cartella di LVGL (se presente nelle dipendenze)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/CMakeLists.txt")
    add_subdirectory(dependencies/lvgl)
endif()

# 3. Configurazione dell'eseguibile/libreria
if(ANDROID)
    # Su Android l'entry-point DEVE essere una libreria condivisa (.so) chiamata 'main'
    add_library(main SHARED ${SOURCES})
    
    # Macro necessaria per attivare le direttive #if defined(__ANDROID__) nel tuo codice C
    target_compile_definitions(main PRIVATE __ANDROID__)
    
    # Cartelle degli header per Android
    target_include_directories(main PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl
    )

    # Link delle librerie native di sistema Android + LVGL
    target_link_libraries(main PRIVATE
        lvgl
        android
        log
        EGL
        GLESv2
    )
else()
    # Configurazione Desktop (Linux / macOS / Windows)
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
