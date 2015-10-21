/***
 *     ██▓     ██▓███   ███▄ ▄███▓   ▓█████ ▒██   ██▒ ██▓███  ▓█████  ██▀███   ██▓ ███▄ ▄███▓▓█████  ███▄    █ ▄▄▄█████▓  ██████ 
 *    ▓██▒    ▓██░  ██▒▓██▒▀█▀ ██▒   ▓█   ▀ ▒▒ █ █ ▒░▓██░  ██▒▓█   ▀ ▓██ ▒ ██▒▓██▒▓██▒▀█▀ ██▒▓█   ▀  ██ ▀█   █ ▓  ██▒ ▓▒▒██    ▒ 
 *    ▒██░    ▓██░ ██▓▒▓██    ▓██░   ▒███   ░░  █   ░▓██░ ██▓▒▒███   ▓██ ░▄█ ▒▒██▒▓██    ▓██░▒███   ▓██  ▀█ ██▒▒ ▓██░ ▒░░ ▓██▄   
 *    ▒██░    ▒██▄█▓▒ ▒▒██    ▒██    ▒▓█  ▄  ░ █ █ ▒ ▒██▄█▓▒ ▒▒▓█  ▄ ▒██▀▀█▄  ░██░▒██    ▒██ ▒▓█  ▄ ▓██▒  ▐▌██▒░ ▓██▓ ░   ▒   ██▒
 *    ░██████▒▒██▒ ░  ░▒██▒   ░██▒   ░▒████▒▒██▒ ▒██▒▒██▒ ░  ░░▒████▒░██▓ ▒██▒░██░▒██▒   ░██▒░▒████▒▒██░   ▓██░  ▒██▒ ░ ▒██████▒▒
 *    ░ ▒░▓  ░▒▓▒░ ░  ░░ ▒░   ░  ░   ░░ ▒░ ░▒▒ ░ ░▓ ░▒▓▒░ ░  ░░░ ▒░ ░░ ▒▓ ░▒▓░░▓  ░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░   ▒ ▒▓▒ ▒ ░
 *    ░ ░ ▒  ░░▒ ░     ░  ░      ░    ░ ░  ░░░   ░▒ ░░▒ ░      ░ ░  ░  ░▒ ░ ▒░ ▒ ░░  ░      ░ ░ ░  ░░ ░░   ░ ▒░    ░    ░ ░▒  ░ ░
 *      ░ ░   ░░       ░      ░         ░    ░    ░  ░░          ░     ░░   ░  ▒ ░░      ░      ░      ░   ░ ░   ░      ░  ░  ░  
 *        ░  ░                ░         ░  ░ ░    ░              ░  ░   ░      ░         ░      ░  ░         ░                ░  
 *                                                                                                                               
 */

/*
Este programa calcula o variograma numa direção usando a definição diretamente.


Autor: Péricles Lopes Machado

*/

#include <cstdio>

using namespace std;

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

	
	double*** z1 = new double**[N];
	double*** z2 = new double**[N];
	double*** Y = new double**[N];

	for (int i = 0; i < N; ++i) {
		z1[i] = new double*[M];
		z2[i] = new double*[M];

		Y[i] = new double*[M];

		for (int j = 0; j < M; ++j) {
			z1[i][j] = new double[K];
			z2[i][j] = new double[K];
			Y[i][j] = new double[K];

			for (int k = 0; k < K; ++k) {
				fscanf(f1, "%lf", &z1[i][j][k]);
				fscanf(f2, "%lf", &z2[i][j][k]);
			}
		}
	}
	
	fclose(f1);
	fclose(f2);


	printf("%d %d %d\n", N, M, K);

	FILE* fout = fopen("cross_varmap_simple_3d.dat", "w+");
	fprintf(fout, "Cross Varmap simple 3d\n");
	fprintf(fout, "4\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "Z\n");
	fprintf(fout, "varmap\n");

	for (int hx = 0; hx < N; ++hx) {
		for (int hy = 0; hy < M; ++hy) {
			for (int hz = 0; hz < K; ++hz) {
				double acc = 0;
				double accprod = 0;

				for (int i = hx; i < N; ++i) {
					for (int j = hy; j < M; ++j) {
						for (int k = hz; k < K; ++k) {
							double dz = z1[i][j][k] - z2[i - hx][j - hy][k - hz];
							// z[i]² + z[i - h]² - 2 z[i] * z[i-h]
							acc += 	(dz * dz) / (2 * (N - hx) * (M - hy) * (K - hz));
							accprod += z2[i - hx][j - hy][k - hz] * z1[i][j][k];
						}

					}
				}

				printf("%.3lf ", acc);
				printf(" (%.3lf) ", accprod);
				fprintf(fout, "%d %d %d %lf\n", hx, hy, hz, acc);
			}
			printf("\n");
		}
	}
	fclose(fout);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			delete z1[i][j];
			delete z2[i][j];
			delete Y[i][j];
		}
		delete z1[i];
		delete z2[i];
		delete Y[i];
	}

	delete z1;
	delete z2;
	delete Y;

	return 0;
}


