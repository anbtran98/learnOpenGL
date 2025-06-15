cmake_minimum_required(VERSION 3.12 )

project(learnopengl)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_MODULE_PATH "~/")
#set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/glfw3" )

set(GLFW3_DIR "/usr/local/lib/cmake/glfw3")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable( learnopengl src/main.cpp src/glad.c )

target_link_libraries( learnopengl PRIVATE glfw3 OpenGL::GL )
