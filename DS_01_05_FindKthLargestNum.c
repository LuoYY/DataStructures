/*
* Data Structures in C
* Find Kth Largest Num in the unsorted set 
* 20160320
* LuoYingYing
*/


#include <stdio.h>

int FindKthLargest(int S[], int K, int Low, int High);
void Swap(int *a, int *b);

int main(int argc, char const *argv[])
{
	int S[6] = {4,8,6,9,2,5};
	printf("%d\n", FindKthLargest(S, 2, 0, 5));
	return 0;
}

int FindKthLargest(int S[], int K, int Low, int High)
{
 	int Pivot = S[Low];
	int Left = Low, Right = High;
	if (Low >= High)
	{
		return Pivot;
	}
	while(Low < High)
	{
		Swap(&S[Low], &S[High]);
		while(Low < High && S[Low] >= Pivot) Low++;
		while(Low < High && S[High] <= Pivot) High--;
	}
	Swap(&S[Low], &S[Right]);
	if (K <= High - Left)
	{
		return FindKthLargest(S, K, Left, High-1);
	}
	else if(K == High - Left + 1)
	{
		return Pivot;
	}
	else
	{
		return FindKthLargest(S, K - High + Left - 1, High + 1, Right);
	}
}

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}