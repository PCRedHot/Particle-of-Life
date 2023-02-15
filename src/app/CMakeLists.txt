# add_library(app "")

# target_sources(app
#     PRIVATE ${CMAKE_CURRENT_LIST_DIR}/app.cpp
#     PRIVATE ${CMAKE_CURRENT_LIST_DIR}/gui.cpp
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}/app.h
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}/gui.h
# )
# target_include_directories(app
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}
# )

add_subdirectory(particle)

# target_sources(${PROJECT_NAME}
#     PRIVATE ${CMAKE_CURRENT_LIST_DIR}/app.cpp
#     PRIVATE ${CMAKE_CURRENT_LIST_DIR}/gui.cpp
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}/app.h
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}/gui.h
# )

# target_include_directories(${PROJECT_NAME}
#     PUBLIC ${CMAKE_CURRENT_LIST_DIR}
# )

file(GLOB HEADER_FILE
     "*.h"
)

file(GLOB CPP_FILE
     "*.cpp"
)


target_sources(${PROJECT_NAME}
    PRIVATE ${CPP_FILE}
    PUBLIC ${HEADER_FILE}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)