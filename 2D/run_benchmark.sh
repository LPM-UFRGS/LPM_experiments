#!/usr/bin/bash

g++ -O2 -o variogram_simple variogram_simple_2d.cpp -lm 
g++ -O2 -o variogram_fft variogram_fft_2d.cpp -lm -lfftw3 -lfftw3l

echo "Running variogram simple..."
echo "Testing simple N = 10 M = 10..."
time ./variogram_simple < t_10_10.in > t_10_10.s.out


echo "Testing simple N = 100 M = 100 ..."
time ./variogram_simple < t_100_100.in > t_100_100.s.out

echo "======================================"

echo "Running variogram FFT..."
echo "Testing FFT N = 10 M = 10..."
time ./variogram_fft < t_10_10.in > t_10_10.fft.out
#diff t_10_10.s.out t_10_10.fft.out


echo "Testing FFT N = 100 M = 100 ..."
time ./variogram_fft < t_100_100.in > t_100_100.fft.out
#diff t_100_100.s.out t_100_100.fft.out

echo "Testing FFT N = 1000 M = 1000 ..."
time ./variogram_fft < t_1000_1000.in > t_1000_1000.fft.out

echo "======================================"




