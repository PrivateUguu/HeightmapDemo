cmake_minimum_required (VERSION 3.8)

project(HeightmapDemo)

set(GLAD_DIR "src/glad/")
set(SFML_LIBRARIES "" CACHE PATH "Directory where SFML libs are located.")
set(SFML_INCLUDES "" CACHE PATH "Directory where SFML headers are located.")
set(GLM_INCLUDES "" CACHE PATH "Directory where GLM headers are located.")

file(GLOB SOURCE src/*.cpp)
file(GLOB HEADERS src/*.h)
add_executable(TerrainDemo "${SOURCE}" "${GLAD_DIR}/glad.c" "${HEADERS}" )

# So ALL_BUILD doesn't get set as startup.
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TerrainDemo)

# Glad includes
target_include_directories(TerrainDemo PRIVATE "${GLAD_DIR}")

# SFML includes and links
target_include_directories(TerrainDemo PRIVATE "${SFML_INCLUDES}")
target_link_directories(TerrainDemo PRIVATE "${SFML_LIBRARIES}")

# GLM includes
target_include_directories(TerrainDemo PRIVATE "${GLM_INCLUDES}")

target_link_libraries(TerrainDemo sfml-system-d sfml-main-d sfml-window-d)