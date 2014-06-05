cmake_minimum_required(VERSION 2.8)


set(PROJECT_NAME variogram_3D)

project(${PROJECT_NAME})



include_directories(${CMAKE_SOURCE_DIR}/3D)

foreach(dir ${PROJ_DIRS})
  add_subdirectory(${dir})
endforeach()


add_executable(gen_data_3d gen_data.cpp)
add_executable(variogram_simple_3d variogram_simple_3d.cpp)
add_executable(variogram_fft_3d variogram_fft_3d.cpp)

target_link_libraries(variogram_fft_3d 
${FFTW_LIB} 
${FFTWL_LIB})



