cmake_minimum_required(VERSION 2.8)


set(PROJECT_NAME variogram_2D)

project(${PROJECT_NAME})



include_directories(${CMAKE_SOURCE_DIR}/2D)

foreach(dir ${PROJ_DIRS})
  add_subdirectory(${dir})
endforeach()


add_executable(gen_data_2d gen_data.cpp)
add_executable(variogram_simple_2d variogram_simple_2d.cpp)
add_executable(variogram_fft_2d variogram_fft_2d.cpp)

target_link_libraries(variogram_fft_2d 
${FFTW_LIB} 
${FFTWL_LIB})



