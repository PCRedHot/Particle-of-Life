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


target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/app.cpp
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/gui.cpp
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/app.h
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/gui.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)