# -- eCP Library --
# Not super good and only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/include/eCP/index/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/src/eCP/index/*.cpp")

add_library(eCPLib ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(eCPLib
  PUBLIC
    ./
    ../include/
)


# -- Utilities Library --
add_library(utilLib eCP/utilities/utilities.cpp)

# To find headers for utilLib
target_include_directories(utilLib
  PUBLIC
    ./
    ../include/
)

target_link_libraries(utilLib
  PUBLIC
  eCPLib
)


# -- Debugging Library --
add_library(debugLib eCP/debugging/debug_tools.cpp)

# To find headers for debugLib
target_include_directories(debugLib
  PUBLIC
    ./
    ../include/
)

target_link_libraries(debugLib
  PUBLIC
    eCPLib
)
