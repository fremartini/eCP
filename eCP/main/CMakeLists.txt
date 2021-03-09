add_executable(main main.cpp)

# To find headers for main
target_include_directories(main 
    PUBLIC 
        ../include
)

target_link_libraries(main 
    PUBLIC
        eCPLib
        utilLib
        debugLib
        ittnotify
)
