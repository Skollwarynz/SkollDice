cmake_minimum_required(VERSION 3.15)
project(SkollDice_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cerchiamo yaml-cpp (necessario per il progetto)
find_package(yaml-cpp REQUIRED)

# Puntiamo alla cartella corretta con il nome esatto
add_subdirectory(SkollDice_Dekstop)
