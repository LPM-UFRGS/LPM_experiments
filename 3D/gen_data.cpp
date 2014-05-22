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
	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < K; ++k) {
				printf("%d ", rand() % 200);
			}
			printf("\n");
		}
	}

	return 0;
}

