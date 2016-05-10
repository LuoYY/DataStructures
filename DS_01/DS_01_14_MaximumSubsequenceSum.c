/*
* Data Structures in C
* Maximum Subsequence Sum
* 20160505
* LuoYingYing
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int N, i, result = 0, maxSubseqSum = -1;
	int first = -1, last = -1, ftmp = 0;
	scanf("%d", &N);
	int *S = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; ++i)
	{
		int tmp;
		scanf("%d", &tmp);
		result += tmp;
		S[i] = tmp;
		if (result > maxSubseqSum)
		{
			maxSubseqSum = result;
			first = ftmp;
			last = i;
		}
		if (result < 0)
		{
			result = 0;
			ftmp = i+1;
		}
	}
	if (first == -1  && last == -1)
	{
		printf("0 %d %d\n", S[0], S[N-1]);
	}
	else
	{
		printf("%d %d %d\n", maxSubseqSum, S[first], S[last]);
	}
	return 0;
}