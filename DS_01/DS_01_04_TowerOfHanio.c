/*
* Data Structures in C
* Tower of Hanoi
* 20160320
* LuoYingYing
*/


#include <stdio.h>

void Move(int n, int start, int goal, int temp);

int main(int argc, char const *argv[])
{
    Move(10, 1, 3, 2);
    return 0;
}

void Move(int n, int start, int goal, int temp)
{
    if(n == 0) return;
    Move(n-1, start, temp, goal);
    printf("Move the disk %d from %d to %d.\n", n, start, goal);
    Move(n-1, temp, goal, start);
}