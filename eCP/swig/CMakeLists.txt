# Include SWIG w. cmake
include(UseSWIG)

# Check and include Python libraries
find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_PATH})

set_property(SOURCE eCP.i PROPERTY CPLUSPLUS ON "-builtin" "-extranative" "-Wall")
set_property(SOURCE eCP.i PROPERTY SWIG_MODULE_NAME eCP_wrapper)

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
