/*
* Data Structures in C
* Calc the distance that ball through
* When it falls from a height and has 90 percent rebound
* It ends up with its height less than 1e-6
* 20160328
* LuoYingYing
*/

#include <stdio.h>

double CalcDistance(double h);

int main(int argc, char const *argv[])
{
	printf("%.6f\n", CalcDistance(10));
	return 0;
}

double CalcDistance(double h)
{
	if ( 0.9*h < 1e-6)
	{
		return h;
	}
	else
	{
		return h + 0.9*h + CalcDistance(0.9*h);
	}
}