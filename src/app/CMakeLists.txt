# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gui)

# add_library(App app.cpp)
# string(APPEND PROJECT_LIBS App)

add_subdirectory(gui)
target_sources(${PROJECT_NAME} PRIVATE app.cpp)