cmake_minimum_required(VERSION 3.21)
project(SudokuGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Concurrent
        REQUIRED)

add_executable(SudokuGame main.cpp Board.cpp Board.h Solver.cpp Solver.h)

target_link_libraries(SudokuGame
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Concurrent
        )

