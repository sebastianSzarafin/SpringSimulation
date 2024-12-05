cmake_minimum_required(VERSION 3.27)
project(SymFizLab1)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------ INCLUDE SDL2 ------------------------------
find_package(SDL2 REQUIRED)
# -------------------------------------------------------------------------

add_subdirectory(external)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/TimedLoop)

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hh)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    glm
    imgui
    implot
)
