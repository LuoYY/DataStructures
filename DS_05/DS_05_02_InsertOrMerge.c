/*
* Data Structures in C
* Insert or Merge
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
void MergeSortByNonRecursiveImpl(ElementType S[], ElementType CmpS[], long N);
void MergePass(ElementType S[], ElementType TmpS[], long N, long length);
void Merge2(ElementType S[], ElementType TmpS[], long L, long R, long RightEnd);
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
        MergeSortByNonRecursiveImpl(TmpS, CmpS, N);
        printf("Merge Sort\n");
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

void MergeSortByNonRecursiveImpl(ElementType S[], ElementType CmpS[], long N)
{
    long i;
    long length = 1;
    bool OneMoreIteration = false;
    ElementType *TmpS = malloc(N * sizeof(ElementType));
    while (length < N)
    {
        MergePass(S, TmpS, N, length);
        length *= 2;
        if (IsCommon(TmpS, CmpS, N) || OneMoreIteration)
        {
            if (OneMoreIteration)
            {
                CopyFunc(TmpS, S, N);
                break;
            }
            else
            {
                OneMoreIteration = true;
            }
        }
        MergePass(TmpS, S, N, length);
        length *= 2;
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
    free(TmpS);
}

void MergePass(ElementType S[], ElementType TmpS[], long N, long length)
{
    long i, j;
    for (i = 0; i <= N - 2 * length; i += 2 * length)
    {
        Merge2(S, TmpS, i, i + length, i + 2 * length - 1);
    }
    if (i + length < N)
    {
        Merge2(S, TmpS, i, i + length, N - 1);
    }
    else
    {
        for (j = i; j < N; ++j)
        {
            TmpS[j] = S[j];
        }
    }
}

void Merge2(ElementType S[], ElementType TmpS[], long L, long R, long RightEnd)
{
    long LeftEnd = R - 1;
    long Tmp = L;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (S[L] <= S[R])
        {
            TmpS[Tmp++] = S[L++];
        }
        else
        {
            TmpS[Tmp++] = S[R++];
        }
    }
    while (L <= LeftEnd)
    {
        TmpS[Tmp++] = S[L++];
    }
    while (R <= RightEnd)
    {
        TmpS[Tmp++] = S[R++];
    }
}

void CopyFunc(ElementType A[], ElementType B[], long N)
{
    long i;
    for ( i = 0; i < N; i++)
    {
        B[i] = A[i];
    }
}