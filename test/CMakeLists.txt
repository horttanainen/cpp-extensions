project(Tests)

file(
    GLOB SOURCE_FILES
    *.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    )

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${cppext_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    cppext
    gtest
    gmock_main
)

