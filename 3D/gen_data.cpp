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

#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;


int main()
{
	srand(time(NULL));
	
	int N, M, K;
	scanf("%d%d%d", &N, &M, &K);

	printf("%d %d %d\n", N, M, K);

	FILE* fout = fopen("data_3d.dat", "w+");

	fprintf(fout, "Varmap fft 3d\n");
	fprintf(fout, "4\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "Z\n");
	fprintf(fout, "data\n");

	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < K; ++k) {
				double v = rand() % 200;
				printf("%lf ", v);
				fprintf(fout, "%d %d %d %lf\n", i, j, k, v);
			}
			printf("\n");
		}
	}
	fclose(fout);

	return 0;
}

