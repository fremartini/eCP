cmake_minimum_required(VERSION 3.18)

project(
    ECP
    VERSION 1.0
    DESCRIPTION "eCP algorithm C++ implementation"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE on)

# External dependencies not installed by CMake
find_package(SWIG COMPONENTS python)
find_package(HDF5 REQUIRED COMPONENTS CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  message("GNU compiler found.")

  list(APPEND generalflags "-Wall")
  message("Appending general flags: " ${generalflags})
  add_compile_options(${generalflags})

  if (${CMAKE_BUILD_TYPE} MATCHES Release)
    list(APPEND relflags "-O3" "-fPIC" )
    message("Build type is: " ${CMAKE_BUILD_TYPE})
    message("Appending further flags: " ${relflags})
    add_compile_options(${relflags})

  elseif (${CMAKE_BUILD_TYPE} MATCHES RelWithDebInfo)
    list(APPEND reldebflags "-g" "-O3" "-fPIC" )
    message("Build type is: " ${CMAKE_BUILD_TYPE})
    message("Appending further flags: " ${reldebflags})
    add_compile_options(${reldebflags})

  elseif (${CMAKE_BUILD_TYPE} MATCHES Debug)
    list(APPEND debugflags "-g" "-Wextra" "-Wpedantic")
    message("Build type is: " ${CMAKE_BUILD_TYPE})
    message("Appending further flags: " ${debugflags})
    add_compile_options(${debugflags})
  endif()

else()
  message(FATAL_ERROR "Current compiler not supported. Only GNU/GCC. Compile options/flags will not be set.")
endif()

# Must be in main CMakeLists.txt file
enable_testing()

# - The compiled library code, executable code, external libs, swig config and tests -
# The compiled library code, executable code, external libs, swig config and tests
add_subdirectory(src)
add_subdirectory(main)
add_subdirectory(extern)
add_subdirectory(tests)
add_subdirectory(swig)

# ------ Good reminders below ------
# Helpers
# message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
# message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
# message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")

# Typical result from above
#CMAKE_CXX_FLAGS_DEBUG is -g
#CMAKE_CXX_FLAGS_RELEASE is -O3 -DNDEBUG
#CMAKE_CXX_FLAGS_RELWITHDEBINFO is -O2 -g -DNDEBUG
#CMAKE_CXX_FLAGS_MINSIZEREL is -Os -DNDEBUG

# Other flags
# list(APPEND extremewarnflags
#   "-Wall" "-Wextra" "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override" "-Wpedantic")
# list(APPEND unknownflags
#   "-fno-rtti" "-fno-exceptions" "-Wno-unused")
