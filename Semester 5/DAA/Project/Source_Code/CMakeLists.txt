
cmake_minimum_required(VERSION 3.21)

project(DAA_Project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)

# Main Qt application
add_executable(DAA_Project
    main.cpp
    GUI/MainWindow.h
    GUI/MainWindow.cpp
    GUI/ClosestPairVisualizer.h
    GUI/ClosestPairVisualizer.cpp
    GUI/KaratsubaVisualizer.h
    GUI/KaratsubaVisualizer.cpp
    GUI/BenchmarkVisualizer.h
    GUI/BenchmarkVisualizer.cpp
    GUI/DatasetPaths.h
    Algorithms/ClosestPair.cpp
    Algorithms/Karatsuba.cpp
)

target_link_libraries(DAA_Project PRIVATE
    Qt6::Widgets
    Qt6::Concurrent
)

# Dataset generator
add_executable(DatasetGenerator
    DatasetGenerator/DatasetGenerator.cpp
)

# Algorithm testing
add_executable(AlgorithmTests
    tests/AlgorithmTests.cpp
    Algorithms/ClosestPair.cpp
    Algorithms/Karatsuba.cpp
)

# Benchmark runner
add_executable(BenchmarkRunner
    Benchmark/BenchmarkRunner.cpp
    Algorithms/ClosestPair.cpp
    Algorithms/Karatsuba.cpp
)