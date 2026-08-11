cmake_minimum_required(VERSION 3.15)
project(MiaApp VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Includi le cartelle per gli header (.h)
include_directories(
    .
    include
    dependencies
    dependencies/lvgl
    dependencies/lvgl/src
)

# Cerca la libreria grafica SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Raccoglie automaticamente i sorgenti (.c)
file(GLOB_RECURSE APP_SOURCES "src/*.c")
file(GLOB_RECURSE LVGL_SOURCES "dependencies/lvgl/src/*.c")

set(SOURCES ${APP_SOURCES} ${LVGL_SOURCES})

# Se c'è un file di risorse icona per Windows (.rc)
if(WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/resources.rc")
    list(APPEND SOURCES resources.rc)
endif()

# Crea l'eseguibile principale
add_executable(${PROJECT_NAME} ${SOURCES})

# Collega SDL2 e la libreria matematica (-lm)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} m)

# Impostazioni specifiche per Windows
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt)
    # Nasconde la finestra del terminale di sfondo in Release
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
