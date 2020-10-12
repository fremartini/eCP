add_library(utilLib utility.cpp)

# To find headers
target_include_directories(utilLib
    PUBLIC
        ./
        ../include
)

add_executable(main main.cpp)
target_compile_features(main PRIVATE cxx_std_17)

# To find header 
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
)