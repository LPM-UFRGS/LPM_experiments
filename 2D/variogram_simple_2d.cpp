/*
Este programa calcula o variograma numa direção usando a definição diretamente.


Autor: Péricles Lopes Machado

*/

#include <cstdio>

using namespace std;

int main()
{
	int N, M;

	scanf("%d%d", &N, &M);

	
	double** z = new double*[N];
	double** Y = new double*[N];

	for (int i = 0; i < N; ++i) {
		z[i] = new double[M];
		Y[i] = new double[M];

		for (int j = 0; j < M; ++j) {
			scanf("%lf", &z[i][j]);
		}
	}


	printf("%d %d\n", N, M);

	FILE* fout = fopen("varmap_simple_2d.dat", "w+");
	fprintf(fout, "Varmap simple 2d\n");
	fprintf(fout, "3\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "varmap\n");

	for (int hx = 0; hx < N; ++hx) {
		for (int hy = 0; hy < M; ++hy) {
			double acc = 0;
			double accprod = 0;

			for (int i = hx; i < N; ++i) {
				for (int j = hy; j < M; ++j) {
					double dz = z[i][j] - z[i - hx][j - hy];
					// z[i]² + z[i - h]² - 2 z[i] * z[i-h]
					acc += 	(dz * dz) / (2 * (N - hx) * (M - hy));
					accprod += z[i - hx][j - hy] * z[i][j];

				}
			}

			printf("%.3lf ", acc);
			printf(" (%.3lf) ", accprod);
			fprintf(fout, "%d %d %lf\n", hx, hy, acc);
		}
		printf("\n");
	}
	fclose(fout);

	for (int i = 0; i < N; ++i) {
		delete z[i];
		delete Y[i];
	}

	delete z;	
	delete Y;

	return 0;
}


