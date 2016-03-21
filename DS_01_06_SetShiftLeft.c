/*
* Data Structures in C
* The set S[N] shift left M digit.
* 20160321
* LuoYingYing
*/


#include <stdio.h>

void ShiftLeft(int S[], int N, int M);

int main(int argc, char const *argv[])
{
	int S[8] = {1,2,3,4,5,6,7,8};
	ShiftLeft(S, 8, 3);
	int i;
	for (i = 0; i < 8; ++i)
	{
		printf("%d\n", S[i]);
	}
	return 0;
}

void ShiftLeft(int S[], int N, int M)
{
	int digit = M % N;
	int i,j;
	for (i = 0; i < digit; ++i)
	{
		int temp = S[0];
		for (j = 0; j < N-1; ++j)
		{
			S[j] = S[j+1];
		}
		S[N-1] = temp;
	}
}