/*
Este programa calcula o variograma numa direção usando a definição diretamente.


Autor: Péricles Lopes Machado

*/

#include <cstdio>

using namespace std;

int main()
{
	int N, M, K;

	scanf("%d%d%d", &N, &M, &K);

	
	double*** z = new double**[N];
	double*** Y = new double**[N];

	for (int i = 0; i < N; ++i) {
		z[i] = new double*[M];
		Y[i] = new double*[M];

		for (int j = 0; j < M; ++j) {
			z[i][j] = new double[K];
			Y[i][j] = new double[K];

			for (int k = 0; k < K; ++k) {
				scanf("%lf", &z[i][j][k]);
			}
		}
	}


	printf("%d %d %d\n", N, M, K);

	for (int hx = 0; hx < N; ++hx) {
		for (int hy = 0; hy < M; ++hy) {
			for (int hz = 0; hz < K; ++hz) {
				double acc = 0;
				double accprod = 0;

				for (int i = hx; i < N; ++i) {
					for (int j = hy; j < M; ++j) {
						for (int k = hz; k < K; ++k) {
							double dz = z[i][j][k] - z[i - hx][j - hy][k - hz];
							// z[i]² + z[i - h]² - 2 z[i] * z[i-h]
							acc += 	(dz * dz) / (2 * (N - hx) * (M - hy) * (K - hz));
							accprod += z[i - hx][j - hy][k - hz] * z[i][j][k];
						}

					}
				}

				printf("%.3lf ", acc);
				printf(" (%.3lf) ", accprod);
			}
			printf("\n");
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			delete z[i][j];
			delete Y[i][j];
		}
		delete z[i];
		delete Y[i];
	}

	delete z;	
	delete Y;

	return 0;
}


