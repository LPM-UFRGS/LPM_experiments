cmake_minimum_required(VERSION 2.8)


set(PROJECT_NAME variogram_1D)

project(${PROJECT_NAME})



include_directories(${CMAKE_SOURCE_DIR}/1D)

foreach(dir ${PROJ_DIRS})
  add_subdirectory(${dir})
endforeach()


add_executable(gen_data_1d gen_data.cpp)
add_executable(variogram_simple_1d variogram_simple_1d.cpp)
add_executable(variogram_fft_1d variogram_fft_1d.cpp)

target_link_libraries(variogram_fft_1d 
${FFTW_LIB} 
${FFTWL_LIB})



