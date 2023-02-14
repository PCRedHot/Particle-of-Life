cmake_minimum_required(VERSION 3.9)

PROJECT(ParticleOfLife)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Linking Packages / Libraries
## Packages
# ### OpenGL, GLU, X11      # I dont think it is needed
if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(OpenGL REQUIRED)
# find_package(GLEW REQUIRED)
# if(NOT OPENGL_FOUND)
#     message("ERROR: OpenGL not found")
# endif(NOT OPENGL_FOUND)
# set(GL_LIBRARY GL GLU X11)


## Submodules
### GLFW, GLEW
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glew/build/cmake)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/include
    PUBLIC ${CMAKE_SOURCE_DIR}/external/glew/include
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/external/glfw/src
)




target_link_libraries(${PROJECT_NAME}
    # GLEW::GLEW
    glew32s
    glfw
)