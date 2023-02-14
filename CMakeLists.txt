cmake_minimum_required(VERSION 3.9)

PROJECT(ParticleOfLife)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)


# Submodules
## GLFW
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
add_subdirectory(external/glfw)