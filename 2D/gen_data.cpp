#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;


int main()
{
	srand(time(NULL));
	
	int N;
	scanf("%d", &N);

	printf("%d\n", N);
	for (int i = 0; i < N; ++i) printf("%d\n", rand() % 200);
	
	return 0;
}
