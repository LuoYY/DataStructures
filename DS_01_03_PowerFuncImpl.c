
/*
* Data Structures in C
* The power func impl in O(logN)
* 20160319
* LuoYingYing
*/



#include <stdio.h>

double powerByRecursiveImpl(double X, int N);
double powerByIterativeImpl(double X, int N);

int main(int argc, char const *argv[])
{
	printf("%f\n",powerByRecursiveImpl(2,4));
	printf("%f\n",powerByIterativeImpl(30,5));
	return 0;
}

double powerByRecursiveImpl(double X, int N)
{
	int result = 1;
	if (N != 0)
	{
		int i;
		int temp = X;
		for (i = 2; i <= N; i *= 2)
		{
			temp *= temp;
		}
		result *= temp;
		result *= powerByRecursiveImpl(X, N-i/2);
	}
	return result;
}


double powerByIterativeImpl(double X, int N)
{
	int result = 1;
	if (N != 0)
	{
		int i, count = N;
		do{
			int temp = X;
			for (i = 2; i <= count; i *= 2)
			{
				temp *= temp;
			}
			result *= temp;
			count = count - i/2;
		}while(count);
	}
	return result;
}