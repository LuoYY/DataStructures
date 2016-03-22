/*
* Data Structures in C
* Sort By Two Different Recursive Impl.
* 20160322
* LuoYingYing
*/

#include <stdio.h>

void Sort1(int S[], int Left, int Right);
void Sort2(int S[], int Left, int Right);
void Swap(int *a, int *b);

int main(int argc, char const *argv[])
{
	int S[7] = {1,5,8,2,9,4,6}, i;
	Sort1(S, 0, 6);
	//Sort2(S, 0, 6);
	for (i = 0; i < 7; ++i)
	{
		printf("%d\n", S[i]);
	}
	return 0;
}

void Sort1(int S[], int Left, int Right)
{
	int i;
	if (Left == Right)
	{
		return;
	}
	for (i = Left; i < Right + 1; ++i)
	{
		if (S[i] < S[Left])
		{
			Swap(&S[i], &S[Left]);
		}
	}
	Sort(S, Left+1, Right);
}

void Sort2(int S[], int Left, int Right)
{
	if (Left == Right)
	{
		return;
	}
	int Center = (Left+Right)/2;
	Sort2(S, Left, Center);
	Sort2(S, Center+1, Right);
	while(S[Center] > S[Center+1])
	{
		Swap(&S[Center], &S[Center+1]);
		int i;
		for (i = Center; i > Left && S[i] < S[i-1]; i--)
		{
			Swap(&S[i], &S[i-1]);
		}
		for (i = Center+1; i < Right && S[i] > S[i+1]; i++)
		{
			Swap(&S[i], &S[i+1]);
		}
	}
}


void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}