cmake_minimum_required(VERSION 3.16)
project(sphere-rendering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED IMPORTED_TARGET sfml-graphics sfml-window sfml-system)

set(SOURCE_DIR source)
set(INCLUDE_DIR include)

file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)

add_executable(sphere-rendering ${SOURCE_FILES})

target_include_directories(sphere-rendering PRIVATE ${INCLUDE_DIR})

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

target_link_libraries(sphere-rendering PkgConfig::SFML)

target_include_directories(sphere-rendering PRIVATE src)

install(TARGETS sphere-rendering DESTINATION bin)
