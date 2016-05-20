/*
* Data Structures in C
* Sort with Swap
* LuoYingYing
* 20160516
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s

int main(int argc, char const *argv[])
{
	long N, i, j, k, Tmp, Sum = 0, Cnt;
	bool IncludeZero;
	scanf("%ld", &N);
	long *S = malloc(N * sizeof(long));
	long *P = malloc(N * sizeof(long));
	for (i = 0; i < N; i++)
	{
		scanf("%ld", &S[i]);
		P[S[i]] = i;
	}
	for (i = 0; i < N; i++)
	{
		Cnt = 0;
		IncludeZero = false;
		if (P[i] != i)
		{
			j = i;
			Tmp = S[j];
			while (P[P[j]] != P[j])
			{
				S[j] = S[P[j]];
				if (S[j] == 0)
				{
					IncludeZero = true;
				}
				Cnt++;
				k = P[j];
				P[j] = j;
				j = k;
			}
			S[j] = Tmp;
			P[j] = j;
			Cnt++;
			if (S[j] == 0)
			{
				IncludeZero = true;
			}
			Cnt += IncludeZero ? -1 : 1;
			Sum += Cnt;
		}
	}
	printf("%ld\n", Sum);
}
