cmake_minimum_required(VERSION 3.13.0)

PROJECT(ParticleOfLife)

set(PROJECT_LIBS "")


# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)



set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# set (CMAKE_CXX_EXTENSIONS OFF)


# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(${PROJECT_NAME} src/main.cpp)

# Link src files
add_subdirectory(src)

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

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    glu32
    opengl32
    freeglut
)

# ## Submodules
# ### GLFW, GLEW
# SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
# add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
# # add_subdirectory(${CMAKE_SOURCE_DIR}/external/glew/build/cmake)
# add_subdirectory(${CMAKE_SOURCE_DIR}/external/glew)

# target_include_directories(${PROJECT_NAME}
#     PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/include
#     PUBLIC ${CMAKE_SOURCE_DIR}/external/glew/include
# )

# # target_link_directories(${PROJECT_NAME}
# #     PRIVATE ${CMAKE_SOURCE_DIR}/external/glfw/src
# #     PRIVATE ${CMAKE_SOURCE_DIR}/external/glew/src
# # )

# target_link_libraries(${PROJECT_NAME}
#     libglew_static
#     glfw
# )


