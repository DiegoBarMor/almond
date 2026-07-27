cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

### Build all example apps as separate executables, including shared sources
file(GLOB EXAMPLE_APPS examples/*/app.cpp)
file(GLOB_RECURSE SHARED_SOURCES CONFIGURE_DEPENDS
    examples/*/src/*.cpp
)

foreach(EXAMPLE_APP ${EXAMPLE_APPS})
    get_filename_component(EXAMPLE_DIR ${EXAMPLE_APP} DIRECTORY)
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_DIR} NAME)
    set(TARGET_NAME app_${EXAMPLE_NAME})

    add_executable(${TARGET_NAME} ${EXAMPLE_APP} ${SHARED_SOURCES})
    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
    target_link_libraries(${TARGET_NAME} PRIVATE sfml-graphics)
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples/${EXAMPLE_NAME}
    )

    ### Copy layout.ndg to the output directory after build
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${EXAMPLE_DIR}/layout.ndg
            $<TARGET_FILE_DIR:${TARGET_NAME}>/layout.ndg
        COMMENT "Copying layout.ndg for ${TARGET_NAME}"
    )
endforeach()
