cmake_minimum_required(VERSION 3.29)
project(Lb2)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        Main.cpp
        Students.cpp
        GUI.h
        #Tests.h
        #Tests.cpp
)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(Lb2 ${SOURCES})

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core Charts)

target_link_libraries(Lb2 PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Charts)
