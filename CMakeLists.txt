cmake_minimum_required(VERSION 4.1)
project(MCPI)

set(CMAKE_CXX_STANDARD 26)

add_executable(MCPI main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(DEPS glfw OpenGL::GL GLEW::GLEW glm::glm)
target_link_libraries(MCPI PRIVATE ${DEPS})
