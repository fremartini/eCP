# Not super good and only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/include/eCP/*.hpp")
file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${ECP_SOURCE_DIR}/src/*.cpp")

add_library(eCP_library ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(eCP_library
    PUBLIC 
        ./
        ../include)

target_compile_features(eCP_library PUBLIC cxx_std_17)

target_link_libraries(eCP_library
    PRIVATE
        ittnotify
)