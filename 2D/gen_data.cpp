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
	for (int i = 0; i < N; ++i) { 
		for (int j = 0; j < M; ++j)
			printf("%d ", rand() % 200);
		printf("\n");
	}

	return 0;
}
