cmake_minimum_required(VERSION 3.15...3.30)
project(EnChess VERSION 1.0)

add_executable(EnChess src/main.c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/findSDL2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_compile_definitions(
  "${CMAKE_PROJECT_NAME}"
  PUBLIC __ASSETS__="${CMAKE_CURRENT_SOURCE_DIR}/src/assets/")

# Find required sdl2 packages and then includes in the project
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(EnChess ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

if(PROJECT_IS_TOP_LEVEL AND UNIX)
  # Create symlink to compile_commands.json for IDE to pick it up
  execute_process(
    COMMAND
      ${CMAKE_COMMAND} -E create_symlink
      ${CMAKE_BINARY_DIR}/compile_commands.json
      ${CMAKE_CURRENT_SOURCE_DIR}/build/compile_commands.json)
endif()
