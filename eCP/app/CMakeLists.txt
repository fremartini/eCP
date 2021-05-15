add_library(utilLib utility.cpp)

# To find headers for utilLib
target_include_directories(utilLib
    PUBLIC
        ./
        ../include
)

target_link_libraries(utilLib
    PUBLIC
        eCP_library
    PRIVATE
        HDF5::HDF5
) 

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)

# To find headers for main
target_include_directories(main 
    PUBLIC 
        ./
        ../include
)

target_link_libraries(main 
    PRIVATE
        utilLib
    PUBLIC
        eCP_library
        ittnotify
)