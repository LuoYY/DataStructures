/*
* Data Structures in C
* Calc the function F(x) = x - x^2 + x^3 - ... - x^N (N > 0)
* 20160329
* LuoYingYing
*/

#include <stdio.h>

double Calc(double x, int n, int coef);

int main(int argc, char const *argv[])
{
	printf("%.3f\n", Calc(2, 5, 1));
	return 0;
}

/* QinJiuShao algorithm */
double Calc(double x, int n, int coef)
{
	if ( n > 1)
	{
		return x * (coef + Calc(x, n-1, -coef));
	}
	else
	{
		return x * coef;
	}
}