cmake_minimum_required(VERSION "3.22")

project(CrossyRoad)

FILE(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp include/*.h)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(RAYGUI_VERSION 3.2)
find_package(raygui ${RAYGUI_VERSION} QUIET)
if (NOT raygui_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/${RAYGUI_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raygui)
  if (NOT raygui_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raygui)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raygui_SOURCE_DIR}/projects/CMake ${raygui_BINARY_DIR})
  endif()
endif()

add_executable(CrossyRoad ${SOURCES})
target_link_libraries(CrossyRoad raylib)
target_link_libraries(CrossyRoad raygui)
target_include_directories(CrossyRoad PRIVATE include)