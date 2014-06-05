#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;


int main()
{
	srand(time(NULL));
	
	int N, M;
	scanf("%d%d", &N, &M);

	printf("%d %d\n", N, M);

	FILE* fout = fopen("data_2d.dat", "w+");
	fprintf(fout, "Varmap fft 2d\n");
	fprintf(fout, "3\n");
	fprintf(fout, "X\n");
	fprintf(fout, "Y\n");
	fprintf(fout, "data\n");

	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < M; ++j) {
			double v = rand() % 200;
			printf("%lf ", v);
			fprintf(fout, "%d %d %lf\n", i, j, v);
		
		}
		printf("\n");
	}
	fclose(fout);

	return 0;
}
