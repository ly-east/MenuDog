cmake_minimum_required(VERSION 3.15.0)

# ref: https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
if (POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif (POLICY CMP0091)

project(MenuDog VERSION 0.1.0 LANGUAGES CXX)

configure_file(
  ${CMAKE_SOURCE_DIR}/include/Version.h.in
  ${CMAKE_SOURCE_DIR}/include/Version.h
  @ONLY
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/output)
set(CMAKE_INSTALL_BINDIR ".")
set(CMAKE_INSTALL_LIBDIR ".")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(minQt6Version 6.5)

list(APPEND CMAKE_PREFIX_PATH "D:/qt/6.5.3/msvc2019_64/lib/cmake")
find_package(Qt6 ${minQt6Version} REQUIRED COMPONENTS Core Widgets LinguistTools)

enable_testing()

add_subdirectory(lib)
add_subdirectory(third-party)
