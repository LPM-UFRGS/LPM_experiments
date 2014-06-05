/*
Este programa calcula o variograma numa direção usando FFT para acelarar o cálculo.


Autor: Péricles Lopes Machado

*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fftw3.h>
     
#define REAL 0
#define IMAG 1

using namespace std;

#define _p(i, j, k) [((i) * M + (j)) * K + (k)]
#define _p3(i, j, k) [((i) * (2 * M + 1) + (j)) * (2 * K + 1) + (k)]

int main(int argc, char** argv)
{

	if (argc != 3) {
		printf ("%s <variable_1> <variable_2>", argv[0]);
		return 0;
	}

	int N, M, K;
	FILE* f1 = fopen(argv[1], "r");
	FILE* f2 = fopen(argv[2], "r");
	
	fscanf(f1, "%d%d%d", &N, &M, &K);
	fscanf(f2, "%d%d%d", &N, &M, &K);

	
	double* Y = (double*) malloc(sizeof(double) * N * M * K);
	double* accp11 = (double*) malloc(sizeof(double) * N * M * K);
	double* accp22 = (double*) malloc(sizeof(double) * N * M * K);

	fftw_complex *z1, *Z1, *ZI1;
	fftw_complex *z2, *Z2, *ZI2;

	fftw_plan p;


	int ZS = (2 * N + 1) * (2 * M + 1) * (2 * K + 1);

	z1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	Z1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	ZI1 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	
	z2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	Z2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	ZI2 = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);


	for (int i = 0; i < ZS; ++i) {
		z1[i][REAL] = z1[i][IMAG] = 0;
		z2[i][REAL] = z2[i][IMAG] = 0;
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < K; ++k) {
				accp11 _p(i, j, k) = 0;
				accp22 _p(i, j, k) = 0;
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int  j = 0; j < M; ++j) {
			for (int k = 0; k < K; ++k) {
				double v1, v2;


				fscanf(f1, "%lf", &v1);
				fscanf(f2, "%lf", &v2);
	
				z1 _p3(i, j, k)[REAL] = v1;
				z1 _p3(i, j, k)[IMAG] = 0;
				
				z2 _p3(i, j, k)[REAL] = v2;
				z2 _p3(i, j, k)[IMAG] = 0;

				if (i > 0) {
					if (j > 0) {
						if (k > 0) {
							accp11 _p(i, j, k) = v1 * v1 
							+ accp11 _p(i - 1, j, k) + accp11 _p(i, j - 1, k) + accp11 _p(i, j, k - 1)
							- accp11 _p(i - 1, j - 1, k) - accp11 _p(i - 1, j, k - 1) - accp11 _p(i, j - 1, k - 1)
							+ accp11 _p(i - 1, j - 1, k - 1);
							
							accp22 _p(i, j, k) = v2 * v2 
							+ accp22 _p(i - 1, j, k) + accp22 _p(i, j - 1, k) + accp22 _p(i, j, k - 1)
							- accp22 _p(i - 1, j - 1, k) - accp22 _p(i - 1, j, k - 1) - accp22 _p(i, j - 1, k - 1)
							+ accp22 _p(i - 1, j - 1, k - 1);
						} else {
							accp11 _p(i, j, k) = v1 * v1 
							+ accp11 _p(i - 1, j, k) + accp11 _p(i, j - 1, k) 
							- accp11 _p(i - 1, j - 1, k);
							
							accp22 _p(i, j, k) = v2 * v2 
							+ accp22 _p(i - 1, j, k) + accp22 _p(i, j - 1, k) 
							- accp22 _p(i - 1, j - 1, k);
						}
					} else {
						if (k > 0) {
							accp11 _p(i, j, k) = v1 * v1 
							+ accp11 _p(i - 1, j, k) + accp11 _p(i, j, k - 1)
							- accp11 _p(i - 1, j, k - 1);
							
							accp22 _p(i, j, k) = v2 * v2 
							+ accp22 _p(i - 1, j, k) + accp22 _p(i, j, k - 1)
							- accp22 _p(i - 1, j, k - 1);
						} else {
							accp11 _p(i, j, k) = v1 * v1 + accp11 _p(i - 1, j, k);
							
							accp22 _p(i, j, k) = v2 * v2 + accp22 _p(i - 1, j, k);
						}
					}
				} else {
					if (j > 0) {
						if (k > 0) {
							accp11 _p(i, j, k) = v1 * v1 
							+ accp11 _p(i, j - 1, k) + accp11 _p(i, j, k - 1)
							- accp11 _p(i, j - 1, k - 1);
							
							accp22 _p(i, j, k) = v2 * v2 
							+ accp22 _p(i, j - 1, k) + accp22 _p(i, j, k - 1)
							- accp22 _p(i, j - 1, k - 1);
						} else {
							accp11 _p(i, j, k) = v1 * v1 + accp11 _p(i, j - 1, k);
							
							accp22 _p(i, j, k) = v2 * v2 + accp22 _p(i, j - 1, k);
						}
					} else {
						if (k > 0) {
							accp11 _p(i, j, k) = v1 * v1 + accp11 _p(i, j, k - 1);
							
							accp22 _p(i, j, k) = v2 * v2 + accp22 _p(i, j, k - 1);
						} else {
							accp11 _p(i, j, k) = v1 * v1;
							
							accp22 _p(i, j, k) = v2 * v2;
						}
					}
				}
			}
		}
	}
	
	fclose(f1);
	fclose(f2);

	//LEVA z para o dominio da frequencia

	p = fftw_plan_dft_3d(2 * N + 1, 2 * M + 1, 2 * K + 1, z1, Z1, FFTW_FORWARD, FFTW_ESTIMATE);
	
	fftw_execute(p);
	
	p = fftw_plan_dft_3d(2 * N + 1, 2 * M + 1, 2 * K + 1, z2, Z2, FFTW_FORWARD, FFTW_ESTIMATE);
	
	fftw_execute(p);



	//Realiza convolução
	for (int h = 0; h < ZS; ++h) {
		double a = Z1[h][REAL] * Z2[h][REAL] + Z1[h][IMAG] * Z2[h][IMAG];
		double b = - Z1[h][REAL] * Z2[h][IMAG] + Z1[h][IMAG] * Z2[h][REAL];
		
		Z1[h][REAL] =  a;
		Z1[h][IMAG] =  b;
	}


	p = fftw_plan_dft_3d(2 * N + 1, 2 * M + 1, 2 * K + 1, Z1, ZI1, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p); 

	printf("%d %d %d\n", N, M, K);

	FILE* fout = fopen("cross_varmap_fft_3d.dat", "w+");
	fprintf(fout, "Cross Varmap fft 3d\n");
	fprintf(fout, "4\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "Z\n");
	fprintf(fout, "varmap\n");

	for (int hx = 0; hx < N; ++hx) { 
		for (int hy = 0; hy < M; ++hy) {
			for (int hz = 0; hz < K; ++hz) {

				/*

				Y[h] = SUM( i = h .. N(h),  (z1[i] - z2[i - h])²) / (2 * N(h))


				Y[h] =  
				SUM( i = h .. N(h),  z2[i - h]²) / (2 * N(h)) [S1]
				+ 
				SUM( i = h .. N(h),  z1[i]²) / (2 * N(h)) [S2]
				- 2 *
				SUM( i = h .. N(h),  z1[i] * z2[i - h]) / (2 * N(h)) [S3] 
				*/

				double S3 = ZI1 _p3(hx, hy, hz)[REAL] / ZS;
				
				double S2 = accp11 _p(N - 1, M  - 1, K - 1);

				if (hx > 0) S2 -= accp11 _p(hx - 1, M  - 1, K - 1);
				if (hy > 0) S2 -= accp11 _p(N  - 1, hy - 1, K - 1);
				if (hz > 0) S2 -= accp11 _p(N  - 1, M -  1, hz - 1);

				if (hx > 0 && hy > 0) S2 += accp11 _p(hx - 1, hy - 1, K - 1); 
				if (hx > 0 && hz > 0) S2 += accp11 _p(hx - 1, M  - 1, hz - 1);
				if (hy > 0 && hz > 0) S2 += accp11 _p(N  - 1, hy - 1, hz - 1); 

				if (hx > 0 && hy > 0 && hz > 0) S2 -= accp11 _p(hx - 1, hy  - 1, hz - 1);
			
			
				double S1 = accp22 _p(N - hx - 1, M - hy - 1, K - hz - 1);

			
				Y _p(hx, hy, hz) =        S1 / (2 * (N - hx) * (M - hy) * (K - hz)) 
								+     S2 / (2 * (N - hx) * (M - hy) * (K - hz)) 
								- 2 * S3 / (2 * (N - hx) * (M - hy) * (K - hz));

				printf("%.3lf ", Y _p(hx, hy, hz) );
				//printf(" (%.3lf) ", S3);
				fprintf(fout, "%d %d %d %lf\n", hx, hy, hz, Y _p(hx, hy, hz));
			}
			printf("\n");
		}
	}
	fclose(fout);
	


	free(Y);
	free(accp11);
	free(accp22);

	fftw_destroy_plan(p);
	
	fftw_free(z1); 
	fftw_free(Z1);
	fftw_free(ZI1);
	
	fftw_free(z2); 
	fftw_free(Z2);
	fftw_free(ZI2);

	return 0;
}





