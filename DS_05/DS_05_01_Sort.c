/*
* Data Structures in C
* Sort
* LuoYingYing
* 20160514
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s
#define Cutoff 3

typedef long ElementType;

void ReadData(ElementType *S, long N);
void XSort(ElementType S[], long N, int X);
void BubbleSort(ElementType S[], long N);
void InsertionSort(ElementType S[], long N);
void ShellSort(ElementType S[], long N);
void HeapSort(ElementType S[], long N);
void BuildMaxHeap(ElementType S[], long N);
void TuneMaxHeap(ElementType S[], long index, long N);
void Swap(ElementType *a, ElementType *b);
void MergeSortByRecursiveImpl(ElementType S[], long N);
void MSort(ElementType S[], ElementType TmpS[], long L, long RightEnd);
void Merge1(ElementType S[], ElementType TmpS[], long L, long R, long RightEnd);
void MergeSortByNonRecursiveImpl(ElementType S[], long N);
void MergePass(ElementType S[], ElementType TmpS[], long N, long length);
void Merge2(ElementType S[], ElementType TmpS[], long L, long R, long RightEnd);
void QuickSort(ElementType S[], long N);
void QSort(ElementType S[], long L, long R);
void Median3(ElementType S[], long L, long R, ElementType *Pivot);

int main(int argc, char const *argv[])
{
    long N, i;
    bool IsFirst = true;
    scanf("%ld", &N);
    ElementType *S = malloc(N * sizeof(ElementType));
    ReadData(S, N);
    XSort(S, N, 5);
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
        printf("%ld", S[i]);
    }
    printf("\n");
    return 0;
}

void ReadData(ElementType *S, long N)
{
    long i;
    for (i = 0; i < N; i++)
    {
        //scanf("%ld", &S[i]);
        S[i] = i;
    }
}

void XSort(ElementType S[], long N, int X)
{
    switch (X)
    {
        case 0: BubbleSort(S, N); break;
        case 1: InsertionSort(S, N); break;
        case 2: ShellSort(S, N); break;
        case 3: HeapSort(S, N); break;
        case 4: MergeSortByRecursiveImpl(S, N); break;
        case 5: MergeSortByNonRecursiveImpl(S, N); break;
        case 6: QuickSort(S, N); break;
        default: BubbleSort(S, N); break;
    }
}

void BubbleSort(ElementType S[], long N)
{
    long i, j, flag;
    for (i = N - 1; i >= 0; --i)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (S[j] > S[j + 1])
            {
                Swap(&S[j], &S[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
}

void InsertionSort(ElementType S[], long N)
{
    long i, j, tmp;
    for (i = 1; i < N; i++)
    {
        tmp = S[i];
        for (j = i; j > 0 && S[j - 1] > tmp; j--)
        {
            S[j] = S[j - 1];
        }
        S[j] = tmp;
    }
}

void ShellSort(ElementType S[], long N)
{
    long i, j, k, tmp;
    long D;
    long Sedgewick[] = { 146305, 64769, 36289, 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1, 0 };
    for (i = 0; Sedgewick[i] > 0; i++)
    {
        D = Sedgewick[i];
        if (D < N)
        {
            for (j = D; j < N; j++)
            {
                tmp = S[j];
                for (k = j; k >= D && S[k - D] > tmp; k -= D)
                {
                    S[k] = S[k - D];
                }
                S[k] = tmp;
            }
        }
    }
}

void HeapSort(ElementType S[], long N)
{
    long i;
    BuildMaxHeap(S, N);
    for (i = N - 1; i > 0; i--)
    {
        Swap(&S[0], &S[i]);
        TuneMaxHeap(S, 0, i);
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

void Swap(ElementType *a, ElementType *b)
{
    ElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

void MergeSortByRecursiveImpl(ElementType S[], long N)
{
    ElementType *TmpS = malloc(N * sizeof(ElementType));
    MSort(S, TmpS, 0, N - 1);
    free(TmpS);
}

void MSort(ElementType S[], ElementType TmpS[], long L, long RightEnd)
{
    long Center;
    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        MSort(S, TmpS, L, Center);
        MSort(S, TmpS, Center + 1, RightEnd);
        Merge1(S, TmpS, L, Center + 1, RightEnd);
    }
}

void Merge1(ElementType S[], ElementType TmpS[], long L, long R, long RightEnd)
{
    long i;
    long LeftEnd = R - 1;
    long Tmp = L;
    long NumOfElements = RightEnd - L + 1;
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
    for (i = 0; i < NumOfElements; i++)
    {
        S[RightEnd] = TmpS[RightEnd];
        RightEnd--;
    }
}

void MergeSortByNonRecursiveImpl(ElementType S[], long N)
{
    long length = 1;
    ElementType *TmpS = malloc(N * sizeof(ElementType));
    while (length < N)
    {
        MergePass(S, TmpS, N, length);
        length *= 2;
        MergePass(TmpS, S, N, length);
        length *= 2;
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

void QuickSort(ElementType S[], long N)
{
    QSort(S, 0, N-1);
}

void QSort(ElementType S[], long L, long R)
{
    long i, j, Tmp;
    if (Cutoff >= R - L + 1)
    {
        for (i = L+1; i <= R; i++)
        {
            Tmp = S[i];
            for (j = i; j > L && S[j-1] > Tmp; j--)
            {
                S[j] = S[j-1];
            }
            S[j] = Tmp;
        }
    }
    else
    {
        ElementType Pivot;
        i = L;
        j = R-2;
        Median3(S, L, R, Pivot);
        while(true)
        {
            while(S[++i] < pivot);
            while(S[++j] > pivot);
            if (i < j)
            {
                Swap(&S[i], &S[j]);
            }
            else
            {
                break;
            }
        }
        Swap(&S[i], &S[R-1]);
        QSort(S, L, i-1);
        QSort(S, i+1, R);
    }
}

void Median3(ElementType S[], long L, long R, ElementType *Pivot)
{
    long Center = (L + R)/2;
    if (S[L] > S[Center])
    {
        Swap(&S[L], &S[Center]);
    }
    if (S[L] > S[R])
    {
        Swap(&S[L], &S[R]);
    }
    if (S[Center] > S[R])
    {
        Swap(&S[Center], &S[R]);
    }
    Swap(&S[Center], &S[R-1]);
    *Pivot = S[R-1];
}