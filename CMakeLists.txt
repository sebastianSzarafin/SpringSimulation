cmake_minimum_required(VERSION 3.27)
project(SymFizLab1)

set(CMAKE_CXX_STANDARD 17)

# ------------------------------ INCLUDE SDL2 ------------------------------
find_package(SDL2 REQUIRED)
# -------------------------------------------------------------------------

# ------------------------------ INCLUDE GLM ------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/glm)
# -------------------------------------------------------------------------

# ------------------------------ INCLUDE IMGUI ------------------------------
set(IMGUI_PATH "${PROJECT_SOURCE_DIR}/external/imgui")

file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp)

add_library(IMGUI STATIC ${IMGUI_SOURCES})

# target_link_libraries(IMGUI PUBLIC ${SDL2_LIBRARIES})

set(IMGUI_LIBRARIES IMGUI)
# -------------------------------------------------------------------------

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})

target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hh)

target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${GLM_LIBRARIES}
    ${IMGUI_LIBRARIES}
)
