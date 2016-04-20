/*
* Data Structures in C
* Traversal complete binary search tree by the level order.
* LuoYingYing
* 20160420
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int ElementType;

int cmp(const void *a, const void *b);
int GetSumOfLeft(int N);
void solve(ElementType* S1, ElementType* S2, int left, int right, int root);

int main(int argc, char const *argv[])
{
    int N, i;
    bool isFirstPrint = true;
    ElementType *S1, *S2;
    scanf("%d", &N);
    S1 = (ElementType*)malloc(N*sizeof(ElementType));
    S2 = (ElementType*)malloc(N*sizeof(ElementType));
    for (i = 0; i < N; ++i)
    {
        scanf("%d", &S1[i]);
    }
    qsort(S1, N, sizeof(S1[0]), cmp);
    solve(S1, S2, 0, N-1, 0);
    for (i = 0; i < N; ++i)
    {
        if (!isFirstPrint)
        {
            printf(" ");
        }
        else
        {
            isFirstPrint = false;
        }
        printf("%d", S2[i]);
    }
    return 0;
}

int cmp(const void *a, const void *b)
{
    return  *(ElementType*)a - *(ElementType*)b;
}

int GetSumOfLeft(int N)
{
    int i, delta, sumOfLeft, temp = 1;
    for (i = 0; temp - 1 <= N; ++i)
    {
        temp = temp*2;
    }
    delta = N - (temp/2 - 1);
    if (delta > 0)
    {
        sumOfLeft = (delta < temp/4 ? delta : temp/4) + (temp/2 - 1)/2;
    }
    else
    {
        sumOfLeft = (temp/2 - 1)/2;
    }
    return sumOfLeft;
}

void solve(ElementType* S1, ElementType* S2, int left, int right, int root)
{
    int n, sum, leftRoot, rightRoot;
    if( left <= right)
    {
        n = right - left + 1;
        sum = GetSumOfLeft(n);
        S2[root] = S1[left + sum];
        leftRoot = root * 2 + 1;
        rightRoot = leftRoot + 1;
        solve(S1, S2, left, left + sum - 1, leftRoot);
        solve(S1, S2, left + sum + 1, right, rightRoot);
    }
}
