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


int main(int argc, char** argv)
{

	if (argc != 3) {
		printf ("%s <variable_1> <variable_2>", argv[0]);
		return 0;
	}

	srand(time(NULL));
	
	int N, M, K;
	
	FILE* f1 = fopen(argv[1], "w+");
	FILE* f2 = fopen(argv[2], "w+");
	
	scanf("%d%d%d", &N, &M, &K);

	fprintf(f1, "%d %d %d\n", N, M, K);
	fprintf(f2, "%d %d %d\n", N, M, K);

	FILE* fout = fopen("cross_data_3d.dat", "w+");

	fprintf(fout, "Cross Data 3d\n");
	fprintf(fout, "5\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "Z\n");
	fprintf(fout, "data1\n");
	fprintf(fout, "data2\n");

	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < K; ++k) {
				double v1 = rand() % 200;
				double v2 = rand() % 400;
				
				fprintf(f1, "%lf ", v1);
				fprintf(f2, "%lf ", v2);
				fprintf(fout, "%d %d %d %lf %lf\n", i, j, k, v1, v2);
			}
			fprintf(f1, "\n");
			fprintf(f2, "\n");
		}
	}
	
	fclose(fout);
	fclose(f1);
	fclose(f2);
	
	return 0;
}

