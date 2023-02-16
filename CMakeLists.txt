PROJECT(ParticleOfLife)
cmake_minimum_required(VERSION 3.13.0)

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
if (POLICY CMP0072)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_path(GLUT_INCLUDE_DIR glut.h ${OPENGL_LIBRARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OPENGL_INCLUDE_DIRS}
    PUBLIC ${GLUT_INCLUDE_DIRS}
)


# if (WIN32)
# target_link_libraries(${PROJECT_NAME}
#   ${OPENGL_LIBRARIES}
#   ${GLUT_LIBRARY}
#   glm::glm
#   glu32
#   opengl32
#   freeglut
# )
# else()
target_link_libraries(${PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  glm::glm
)
# endif (WIN32)