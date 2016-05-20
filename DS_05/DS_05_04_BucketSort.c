/*
* Data Structures in C
* Bucket Sort
* LuoYingYing
* 20160515
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s
#define NumOfBuckets 51

int main(int argc, char const *argv[])
{
	int WorkAge;
	long N, i;
	long *Buckets = malloc(NumOfBuckets * sizeof(long));
	for (i = 0; i < NumOfBuckets; ++i)
	{
		Buckets[i] = 0;
	}
	scanf("%ld", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &WorkAge);
		Buckets[WorkAge] += 1;
	}
	for (i = 0; i < NumOfBuckets; ++i)
	{
		if (Buckets[i] > 0)
		{
			printf("%d:%ld\n", i, Buckets[i]);
		}
	}
	return 0;
}