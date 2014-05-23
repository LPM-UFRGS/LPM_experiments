cmake_minimum_required(VERSION 2.8)

# Eliminate a warning when building in Windows that relates
# to static linking of Qt executables to qtmain.lib.
# This policy was introduced in CMake version 2.8.11.
# CMake version 2.8.11.2 warns when the policy is not set
# and uses OLD behavior.
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(LPM_experiments)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING
       "Choose the type of build, options are: Debug Release"
       FORCE )
endif()

#set(FFTWF_LIB  "E:/fftw-3.3.4-dll64/libfftw3f-3.lib")
#set(FFTWL_LIB  "E:/fftw-3.3.4-dll64/libfftw3l-3.lib")
#set(FFTW_LIB  "E:/fftw-3.3.4-dll64/libfftw3-3.lib")
#set(FFTW_ROOT  "E:/fftw-3.3.4-dll64")
#set(FFTW_INCLUDE_DIR  "E:/fftw-3.3.4-dll64")



find_package(FFTW REQUIRED)

include_directories(${FFTW_INCLUDE_DIR})

add_subdirectory(1D)
add_subdirectory(2D)
add_subdirectory(3D)

