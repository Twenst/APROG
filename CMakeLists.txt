cmake_minimum_required(VERSION 3.5)
project(APROG)
list(APPEND CMAKE_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
set(CMAKE_CXX_STANDARD 11)

find_package(Imagine REQUIRED COMPONENTS Graphics Images)

add_executable(APROG main.cpp
               affichage.h affichage.cpp
               objets.h objets.cpp
               constantes.h
               personnage.h personnage.cpp)

target_link_libraries(APROG Imagine::Graphics Imagine::Images)
