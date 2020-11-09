cmake_minimum_required(VERSION 3.18)

include(FetchContent)

# Make googletests part of Makefiles in build dir
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

# Make Intel instrumentatation and tracing api part of build dir
FetchContent_Declare(
  ittapi
  GIT_REPOSITORY https://github.com/intel/ittapi
  GIT_TAG        v3.18.8
)

# Make libs available to the build system
FetchContent_MakeAvailable(googletest ittapi)