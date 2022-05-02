cmake_minimum_required(VERSION 3.13.0)
set(CMAKE_CXX_STANDARD 20)
project(myspace LANGUAGES C CXX)


set(BUILD_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIRECTORY}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIRECTORY}/lib)


## Настройка тестирования:
enable_testing()
add_subdirectory(third_party/googletest)

## Путь из корня:
include_directories(${PROJECT_SOURCE_DIR})

## Библиотеки:
add_subdirectory(libs)

## Сборка подпроектов:
add_subdirectory(phase_analysis)
