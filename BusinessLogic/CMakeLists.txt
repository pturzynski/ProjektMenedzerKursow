cmake_minimum_required(VERSION 3.16)

project(BusinessLogic LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(BusinessLogic SHARED
  BusinessLogic_global.h
  user.h user.cpp
  admin.h admin.cpp
  student.h student.cpp
  exceptions.h exceptions.cpp
  course.h course.cpp
  coursemanager.h coursemanager.cpp


)

target_link_libraries(BusinessLogic PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(BusinessLogic PUBLIC BUSINESSLOGIC_LIBRARY=1)

target_include_directories(BusinessLogic PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)
