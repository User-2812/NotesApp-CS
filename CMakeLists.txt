cmake_minimum_required(VERSION 3.18)
project(NotesApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CopperSpice REQUIRED)

add_executable(NotesApp
  src/main.cpp
  src/mainwindow.cpp
  include/mainwindow.h
)

target_include_directories(NotesApp PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(NotesApp
  CopperSpice::CsCore
  CopperSpice::CsGui
)

