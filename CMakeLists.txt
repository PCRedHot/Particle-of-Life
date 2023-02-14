cmake_minimum_required(VERSION 3.13.0)

PROJECT(ParticleOfLife)

# target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# set (CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

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
find_package(GLUT REQUIRED)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OPENGL_INCLUDE_DIRS}
    PUBLIC ${GLUT_INCLUDE_DIRS}
)


target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    glu32
    opengl32
    freeglut
)

