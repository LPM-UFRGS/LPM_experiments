#!/usr/bin/bash

g++ -O2 -o variogram_simple variogram_simple_1d.cpp -lm 
g++ -O2 -o variogram_fft variogram_fft_1d.cpp -lm -lfftw3 -lfftw3l

echo "Running variogram simple..."
echo "Testing simple N = 10 ..."
time ./variogram_simple < t10.in > t10.s.out


echo "Testing simple N = 1000 ..."
time ./variogram_simple < t1000.in > t1000.s.out

echo "Testing simple N = 10000 ..."
time ./variogram_simple < t10000.in > t10000.s.out

echo "======================================"

echo "Running variogram FFT..."
echo "Testing FFT N = 10 ..."
time ./variogram_fft < t10.in > t10.fft.out
diff t10.s.out t10.fft.out


echo "Testing FFT N = 1000 ..."
time ./variogram_fft < t1000.in > t1000.fft.out
diff t1000.s.out t1000.fft.out

echo "Testing FFT N = 10000 ..."
time ./variogram_fft < t10000.in > t10000.fft.out
diff t10000.s.out t10000.fft.out

echo "Testing FFT N = 100000 ..."
time ./variogram_fft < t100000.in > t100000.fft.out

echo "Testing FFT N = 1000000 ..."
time ./variogram_fft < t1000000.in > t1000000.fft.out

echo "======================================"

