/*
Este programa calcula o variograma numa direção usando a definição diretamente.


Autor: Péricles Lopes Machado

*/

#include <cstdio>

using namespace std;

int main()
{
	int N;
	scanf("%d", &N);

	
	double* z = new double[N];
	double* Y = new double[N];

	for (int i = 0; i < N; ++i) {
		scanf("%lf", &z[i]);
	}


	Y[0] = 0;
	printf("%d\n", N);
	for (int h = 0; h < N; ++h) {
		double acc = 0;
		double accprod = 0;
		for (int i = h; i < N; ++i) {
			double dz = z[i] - z[i - h];
			// z[i]² + z[i - h]² - 2 z[i]z[i-h]
			acc += 	(dz * dz) / (2 * (N - h));
			accprod += z[i] * z[i - h];
		}

		printf("%.3lf ", acc);
		printf(" (%.3lf)\n", accprod);

	}

	delete z;
	delete Y;	
	return 0;
}


