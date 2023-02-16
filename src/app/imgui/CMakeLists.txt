add_subdirectory(backends)

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