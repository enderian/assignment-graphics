cmake_minimum_required(VERSION 3.13)
project(TowerDefence)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
link_libraries(${OPENGL_LIBRARIES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

file(GLOB src "src/*.h" "src/*.cpp")
add_executable(TowerDefence ${src})