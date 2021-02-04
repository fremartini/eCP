include(GoogleTest)

# The individual test files
add_executable(eCP_tests
    distance_tests.cpp
    pre-processing_tests.cpp
    query-processing_tests.cpp
    eCP_tests.cpp
)

# Link required libraries to the test suite
target_link_libraries(eCP_tests eCP_library gtest_main)

add_test(
    NAME eCP_tests
    COMMAND eCP_tests
)
