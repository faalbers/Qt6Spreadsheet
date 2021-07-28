cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Qt6Spreadsheet VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH C:/Qt/6.1.2/mingw81_64)
#set(CMAKE_PREFIX_PATH /Users/frank/Qt/6.1.2/macos)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

file(GLOB QT6SH_SOURCES *.cpp )

add_executable(${PROJECT_NAME} ${QT6SH_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
