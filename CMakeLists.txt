cmake_minimum_required(VERSION 3.29)

project(EmiriEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("3rd/glfw")
add_subdirectory("3rd/spdlog")
add_subdirectory("3rd/mimalloc")
add_subdirectory("3rd/entt")

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} "EnTT")
