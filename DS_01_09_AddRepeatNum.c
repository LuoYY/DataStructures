/*
* Data Structures in C
* The S = a + aa + aaa + ··· + aa···a (n digit)
* 20160324
* LuoYingYing
*/

#include <stdio.h>
long AddRepeatNum(int n, int a);

int main(int argc, char const *argv[])
{
	printf("%ld\n", AddRepeatNum(2, 1));
	return 0;
}

long AddRepeatNum(int n, int a)
{
	long temp = 0, sum = 0;
	while(n--)
	{
		temp = temp*10 + a;
		sum += temp;
	}
	return sum;
}
