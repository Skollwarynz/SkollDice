cmake_minimum_required(VERSION 3.10)
project(MiaApp C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-O3 -Wall)
add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

include_directories(
    .
    include
    dependencies
    dependencies/lvgl
    dependencies/lvgl/src
)

# Usa CMAKE_CURRENT_SOURCE_DIR per trovare i file in modo assoluto e sicuro
file(GLOB APP_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE LVGL_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/src/*.c")

# Unisci le liste
set(SRCS ${APP_SRCS} ${LVGL_SRCS})

add_executable(MiaApp ${SRCS})

if(WIN32)
    target_link_libraries(MiaApp PRIVATE 
        mingw32 
        SDL2main 
        SDL2 
        advapi32 
        bcrypt 
        winmm 
        imm32 
        version 
        setupapi
    )
    target_link_options(MiaApp PRIVATE -mwindows)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(MiaApp PRIVATE ${SDL2_LIBRARIES} m)
endif()
