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

#define _p(i, j) [(i) * M + (j)]
#define _p2(i, j) [(i) * (2 * M + 1) + (j)]

int main()
{
	int N, M;

	scanf("%d%d", &N, &M);


	double* Y = (double*) malloc(sizeof(double) * N * M);
	double* accp = (double*) malloc(sizeof(double) * N * M);

	fftw_complex *z, *Z, *ZI;
	fftw_plan p;


	int ZS = (2 * N + 1) * (2 * M + 1);

	z = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	Z = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);
	ZI = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ZS);


	for (int i = 0; i < ZS; ++i) z[i][REAL] = z[i][IMAG] = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			accp _p(i, j) = 0;
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int  j = 0; j < M; ++j) {
			double v;
			scanf("%lf", &v);

			z _p2(i, j)[REAL] = v;
			z _p2(i, j)[IMAG] = 0;

			if (i > 0) {
				if (j > 0) {
					accp _p(i, j) = v * v + accp _p(i - 1, j) + accp _p(i, j - 1) - accp _p(i - 1, j -1);
				} else {
					accp _p(i, j) = v * v + accp _p(i - 1, j);
				}
			} else {
				if (j > 0) {
					accp _p(i, j) = v * v + accp _p(i, j - 1);
				} else {
					accp _p(i, j) = v * v;
				}
			}
		}
	}

	

	//LEVA z para o dominio da frequencia

	p = fftw_plan_dft_2d(2 * N + 1, 2 * M + 1, z, Z, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p);



	//Realiza convolução
	for (int h = 0; h < ZS; ++h) {
		Z[h][REAL] = Z[h][REAL] * Z[h][REAL] + Z[h][IMAG] * Z[h][IMAG];
		Z[h][IMAG] = 0;
	}


	p = fftw_plan_dft_2d(2 * N + 1, 2 * M + 1, Z, ZI, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p); 

	printf("%d %d\n", N, M);

	for (int hx = 0; hx < N; ++hx) { 
		for (int hy = 0; hy < M; ++hy) {

			/*

			Y[h] = SUM( i = h .. N(h),  (z[i] - z[i - h])²) / (2 * N(h))


			Y[h] =  
			SUM( i = h .. N(h),  z[i - h]²) / (2 * N(h)) [S1]
			+ 
			SUM( i = h .. N(h),  z[i]²) / (2 * N(h)) [S2]
			- 2 *
			SUM( i = h .. N(h),  z[i] * z[i - h]) / (2 * N(h)) [S3] 
			*/

			double S3 = ZI _p2(hx, hy)[REAL] / ZS;

			double S2 = accp _p(N - 1, M  - 1);

			if (hx > 0) S2 -= accp _p(hx - 1, M  - 1);
			if (hy > 0) S2 -= accp _p(N  - 1, hy - 1);
			if (hx > 0 && hy > 0) S2 += accp _p(hx - 1, hy - 1); 
			
			
			double S1 = accp _p(N - hx - 1, M - hy - 1);

			
			Y _p(hx, hy) =        S1 / (2 * (N - hx) * (M - hy)) 
							+     S2 / (2 * (N - hx) * (M - hy)) 
							- 2 * S3 / (2 * (N - hx) * (M - hy));

			printf("%.2lf ", Y _p(hx, hy) );
			printf(" (%.2lf) ", S3);
		}
		printf("\n");
	}

	free(Y);
	free(accp);


	fftw_destroy_plan(p);
	fftw_free(z); 
	fftw_free(Z);
	fftw_free(ZI);

	return 0;
}





