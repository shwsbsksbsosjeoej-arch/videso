cmake_minimum_required(VERSION 3.17)
project(videso LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenCV REQUIRED)

add_subdirectory(external/imgui)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    external/imgui
    capture detection input ui config renderer utils
)

file(GLOB_RECURSE SOURCES
    main.cpp
    capture/*.cpp
    detection/*.cpp
    input/*.cpp
    ui/*.cpp
    config/*.cpp
    renderer/*.cpp
    utils/*.cpp
)

add_executable(videso ${SOURCES})
target_link_libraries(videso
    ${OpenCV_LIBS}
    imgui
    d3d11 dxgi
)
