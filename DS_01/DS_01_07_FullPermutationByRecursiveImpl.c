/*
* Data Structures in C
* Print the full permutation by recursive impl.
* 20160321
* LuoYingYing
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintFullPermutation(int S[], int N, int M);
int *BackUp(int S[], int N);
void Restore(int S[], int *backup, int N);
void Swap(int *a, int *b);
long count = 0;

int main(int argc, char const *argv[])
{
    int N = 7, i;
    clock_t start,end;
    int S[N];
    for (i = 0; i < N; ++i)
    {
        S[i] = i+1;
    }
    start = clock();
    PrintFullPermutation(S, N, 0);
    end = clock();
    printf("Run time: %.3f seconds, Total Count: %ld", (double)(end-start)*1.0/CLK_TCK, count);
    return 0;
}

void PrintFullPermutation(int S[], int N, int M)
{
    if (M == N-1)
    {
        int i;
        for (i = 0; i < N; ++i)
        {
            printf("%d ", S[i]);
        }
        printf("\n");
        count++;
    }
    else
    {
        int i,j;
        for (i = M; i < N; ++i)
        {
            Swap(&S[M], &S[i]);
            int* backup = BackUp(S, N);
            PrintFullPermutation(S, N, M+1);
            Restore(S, backup, N);
        }
    }
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int *BackUp(int S[], int N)
{
    int *backup = (int*)malloc(N*sizeof(int));
    int i;
    for ( i= 0; i < N; ++i)
    {
        backup[i] = S[i];
    }
    return backup;
}

void Restore(int S[], int *backup, int N)
{
    int i;
    for ( i= 0; i < N; ++i)
    {
        S[i] = backup[i];
    }
    free(backup);
}