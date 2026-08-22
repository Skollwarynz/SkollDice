cmake_minimum_required(VERSION 3.10)
project(SkollDice_bin C)

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

file(GLOB APP_SRCS "src/*.c")
file(GLOB_RECURSE LVGL_SRCS "dependencies/lvgl/src/*.c")

if(NOT APP_SRCS)
    file(GLOB APP_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
endif()

if(NOT LVGL_SRCS)
    file(GLOB_RECURSE LVGL_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lvgl/src/*.c")
endif()

set(SRCS ${APP_SRCS} ${LVGL_SRCS})

message(STATUS "Trovati sorgenti app: ${APP_SRCS}")

add_executable(SkollDice_bin ${SRCS})

if(WIN32)
    target_link_libraries(SkollDice_bin PRIVATE 
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
    target_link_options(SkollDice_bin PRIVATE -mwindows)
else()
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(SkollDice_bin PRIVATE ${SDL2_LIBRARIES} m)
endif()
