# Check and include SWIG w. cmake
find_package(SWIG COMPONENTS python)
include(UseSWIG)

# Check and include Python libraries
find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_PATH})

set_property(SOURCE eCP.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE eCP.i PROPERTY SWIG_MODULE_NAME eCP_wrapper)

set_property(SOURCE eCP.i PROPERTY SWIG_COMPILE_OPTIONS
  "-O3; -pthread; -Wno-unused-result; -Wsign-compare; -DNDEBUG; -g; -fwrapv; -O3;
  -Wall; -DOPENSSL_NO_SSL2; -march=x86-64; -mtune=generic; -O2; -pipe; -fno-plt; -fPIC"
)

swig_add_library(eCP_wrapper
  TYPE SHARED
  LANGUAGE python
  SOURCES eCP.i
)

target_include_directories(eCP_wrapper
  PUBLIC
    ../include/
)

swig_link_libraries(eCP_wrapper
  PUBLIC
    ${PYTHON_LIBRARIES}
    eCPLib
)
