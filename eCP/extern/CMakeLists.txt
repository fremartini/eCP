cmake_minimum_required(VERSION 3.18)

include(FetchContent)

# Make googletests part of Makefiles in build dir
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)

    # Create dir structure in build dir
    add_subdirectory(
        ${googletest_SOURCE_DIR}
        ${googletest_BINARY_DIR}
    )
endif()