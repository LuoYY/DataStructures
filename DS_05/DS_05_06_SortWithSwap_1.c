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

void Swap(long *a, long *b);
long Find(long S[], long Elem, long N);
long Check(long S[], long N);

int main(int argc, char const *argv[])
{
	long N, i, a, b, cnt = 0;
	scanf("%ld", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%ld", &S[i]);
	}
	a = Find(S, 0, N);
	while(1)
	{
		if (a != 0)
		{
			b = Find(S, a, N);
			Swap(&S[a], &S[b]);
			a = b;
			cnt++;
		}
		else
		{
			b = Check(S, N);
			if (b == -1)
			{
				break;
			}
			Swap(&S[a], &S[b]);
			a = b;
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}

long Check(long S[], long N)
{
	long i;
	for (i = 0; i < N; i++)
	{
		if (S[i] != i)
		{
			return i;
		}
	}
	return -1;
}

long Find(long S[], long Elem, long N)
{
	long i;
	for (i = 0; i < N; i++)
	{
		if (S[i] == Elem)
		{
			return i;
		}
	}
}

void Swap(long *a, long *b)
{
    long tmp = *a;
    *a = *b;
    *b = tmp;
}