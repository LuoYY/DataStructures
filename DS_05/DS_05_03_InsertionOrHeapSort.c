/*
* Data Structures in C
* Insertion or Heap Sort
* LuoYingYing
* 20160515
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s

typedef long ElementType;

void ReadData(ElementType *S, long N);
bool IsCommon(ElementType S[], ElementType CmpS[], long N);
bool InsertionSort(ElementType S[], ElementType CmpS[], long N);
void HeapSort(ElementType S[], ElementType CmpS[], long N);
void BuildMaxHeap(ElementType S[], long N);
void TuneMaxHeap(ElementType S[], long index, long N);
void Swap(ElementType *a, ElementType *b);
void CopyFunc(ElementType A[], ElementType B[], long N);

int main(int argc, char const *argv[])
{
    long N, i;
    bool IsFirst = true;
    bool IsInsertionSort = false;
    scanf("%ld", &N);
    ElementType *S = malloc(N * sizeof(ElementType));
    ElementType *TmpS = malloc(N * sizeof(ElementType));
    ElementType *CmpS = malloc(N * sizeof(ElementType));
    ReadData(S, N);
    ReadData(CmpS, N);
    CopyFunc(S, TmpS, N);
    IsInsertionSort = InsertionSort(TmpS, CmpS, N);
    if (IsInsertionSort)
    {
        printf("Insertion Sort\n");
    }
    else
    {
        CopyFunc(S, TmpS, N);
        HeapSort(TmpS, CmpS, N);
        printf("Heap Sort\n");
    }
    for (i = 0; i < N; i++)
    {
        if (IsFirst)
        {
            IsFirst = false;
        }
        else
        {
            printf(" ");
        }
        printf("%ld", TmpS[i]);
    }
    printf("\n");
    return 0;
}

void ReadData(ElementType *S, long N)
{
    long i;
    for (i = 0; i < N; i++)
    {
        scanf("%ld", &S[i]);
    }
}

bool IsCommon(ElementType S[], ElementType CmpS[], long N)
{
    long i;
    for (i = 0; i < N; i++)
    {
        if (S[i] != CmpS[i])
        {
            break;
        }
    }
    return i == N ? true : false;
}

bool InsertionSort(ElementType S[], ElementType CmpS[], long N)
{
    long i, j, tmp;
    bool OneMoreIteration = false;
    for (i = 1; i < N; i++)
    {
        tmp = S[i];
        for (j = i; j > 0 && S[j - 1] > tmp; j--)
        {
            S[j] = S[j - 1];
        }
        S[j] = tmp;
        if (IsCommon(S, CmpS, N) || OneMoreIteration)
        {
            if (OneMoreIteration)
            {
                break;
            }
            else
            {
                OneMoreIteration = true;
            }
        }
    }
    return OneMoreIteration ? true : false;
}

void HeapSort(ElementType S[], ElementType CmpS[], long N)
{
    long i;
    bool OneMoreIteration = false;
    BuildMaxHeap(S, N);
    for (i = N - 1; i > 0; i--)
    {
        Swap(&S[0], &S[i]);
        TuneMaxHeap(S, 0, i);
        if (IsCommon(S, CmpS, N) || OneMoreIteration)
        {
            if (OneMoreIteration)
            {
                break;
            }
            else
            {
                OneMoreIteration = true;
            }
        }
    }
}

void BuildMaxHeap(ElementType S[], long N)
{
    long i;
    for (i = N / 2 - 1; i >= 0; i--)
    {
        TuneMaxHeap(S, i, N);
    }
}

void TuneMaxHeap(ElementType S[], long index, long N)
{
    long i, child;
    for (i = index; 2 * i + 1 <= N - 1; i = child)
    {
        child = 2 * i + 1;
        if (child != N - 1 && S[child] < S[child + 1])
        {
            child++;
        }
        if (S[child] > S[i])
        {
            Swap(&S[i], &S[child]);
        }
        else
        {
            break;
        }
    }
}

void CopyFunc(ElementType A[], ElementType B[], long N)
{
    long i;
    for (i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
}

void Swap(ElementType *a, ElementType *b)
{
    ElementType tmp = *a;
    *a = *b;
    *b = tmp;
}