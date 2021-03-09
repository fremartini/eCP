include(GoogleTest)

# -- The individual test files --
add_executable(eCP_tests
  # library
    distance_tests.cpp
    pre-processing_tests.cpp
    query-processing_tests.cpp
    eCP_tests.cpp
    utilities_tests.cpp

  # helpers
    helpers/testhelpers_tests.cpp
)


# -- Link required libraries to the test suite --
target_link_libraries(eCP_tests
  debugLib
  utilLib
  sharedLib
  eCPLib
  gtest_main
  testHelperLib
)

target_include_directories(eCP_tests
  PUBLIC
    ./
)

# -- Adding the test helper lib --
add_library(testHelperLib helpers/testhelpers.cpp)

target_include_directories(testHelperLib
  PUBLIC
  ./
  )

target_link_libraries(testHelperLib eCPLib)

add_test(
    NAME eCP_tests
    COMMAND eCP_tests
)
