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

int main()
{
	int N;

	scanf("%d", &N);


	double* Y = (double*) malloc(sizeof(double) * N);
	double* accp = (double*) malloc(sizeof(double) * N);

	fftw_complex *z, *Z, *ZI;
	fftw_plan p;


	z = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2 * N + 1));
	Z = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2 * N + 1));
	ZI = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * (2 * N + 1));


	for (int i = 0; i < N; ++i) {
		double v;
		scanf("%lf", &v);
		z[i][REAL] = v;
		z[i][IMAG] = 0;

		if (i == 0) accp[i] = v;
		else accp[i] = accp[i-1] + v * v;
	}

	for (int i = N; i < 2 * N + 1; ++i) z[i][REAL] = z[i][IMAG] = 0;


	//LEVA z para o dominio da frequencia

	p = fftw_plan_dft_1d(2 * N + 1, z, Z, FFTW_FORWARD, FFTW_ESTIMATE);

	fftw_execute(p);



	//Realiza convolução
	for (int h = 0; h < 2 *N + 1; ++h) {
		Z[h][REAL] = Z[h][REAL] * Z[h][REAL] + Z[h][IMAG] * Z[h][IMAG];
		Z[h][IMAG] = 0;
	}


	p = fftw_plan_dft_1d(2 * N + 1, Z, ZI, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(p); 

	for (int h = 0; h < N; ++h) {

		/*

		Y[h] = SUM( i = h .. N(h),  (z[i] - z[i - h])²) / (2 * N(h))


		Y[h] =  
		SUM( i = h .. N(h),  z[i - h]²) / (2 * N(h)) [S1]
		+ 
		SUM( i = h .. N(h),  z[i]²) / (2 * N(h)) [S2]
		- 2 *
		SUM( i = h .. N(h),  z[i] * z[i - h]) / (2 * N(h)) [S3] 
		*/

		double S3 = ZI[h][REAL] / (2 * N + 1);

		double S2 = (accp[N - 1] - accp[h] + z[h][REAL] * z[h][REAL]);
		double S1 = (accp[N - h - 1] - accp[0] + z[0][REAL] * z[0][REAL]);

		Y[h] = S1 / (2 * (N - h)) + S2 / (2 * (N - h)) - 2 * S3 / (2 * (N - h));
		printf("%.3lf\n", Y[h]);
		//printf("%.3lf\n", S3);
	}

	free(Y);
	free(accp);


	fftw_destroy_plan(p);
	fftw_free(z); 
	fftw_free(Z);
	fftw_free(ZI);

	return 0;
}





