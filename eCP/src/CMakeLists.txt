# -- eCP Library --
# Not super good and only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/include/eCP/index/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/src/eCP/index/*.cpp")

add_library(eCP_library ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(eCP_library
  PUBLIC
  ../include/
  )


# -- Utilities Library --
add_library(utilLib eCP/utilities/utility.cpp)

# To find headers for utilLib
target_include_directories(utilLib
  PUBLIC
  ../include/
  )

target_link_libraries(utilLib
  PUBLIC
  eCP_library
  )
