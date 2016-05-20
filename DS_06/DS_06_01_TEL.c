/*
* Data Structures in C
* Chat with someone
* LuoYingYing
* 20160517
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 12

typedef struct HTable *HashTable;
typedef struct CellNode *Cell;

struct HTable
{
    long TableSize;
    Cell *TheCells;
};

struct CellNode
{
    char* Data;
    long Cnt;
};

HashTable CreateHashTable(long N);
long Find(HashTable H, char *Elem);
void Insert(HashTable H, char *Elem);
long Hash(char *Data, long N);
long getNextPrime(long N);
bool IsPrime(long N);
void StrCpy(char *A, char *B);
int StrCmp(char *A, char *B);

int main(int argc, char const *argv[])
{
    long N, i, MaxCnt = 0, MaxIndex = 0, Cnt, NumOfMax = 0;
    char *TelNum, *Tel;
    TelNum = malloc(LENGTH * sizeof(char));
    scanf("%ld", &N);
    HashTable H = CreateHashTable(N);
    for (i = 0; i < 2 * N; i++)
    {
        scanf("%s", TelNum);
        Insert(H, TelNum);
    }
    for (i = 0; i < H->TableSize; i++)
    {
        Cnt = H->TheCells[i]->Cnt;
        Tel = H->TheCells[i]->Data;
        if (Cnt != 0 &&
            (Cnt > MaxCnt ||
            (Cnt == MaxCnt && (StrCmp(Tel, H->TheCells[MaxIndex]->Data) == 1))))
        {
            MaxCnt = Cnt;
            MaxIndex = i;
        }
    }
    for (i = 0; i < H->TableSize; i++)
    {
        Cnt = H->TheCells[i]->Cnt;
        if (MaxCnt == Cnt)
        {
            NumOfMax++;
        }
    }
    if (NumOfMax > 1)
    {
        printf("%s %ld %ld\n", H->TheCells[MaxIndex]->Data, MaxCnt, NumOfMax);
    }
    else
    {
        printf("%s %ld\n", H->TheCells[MaxIndex]->Data, MaxCnt);
    }
    return 0;
}


HashTable CreateHashTable(long N)
{
    long i;
    HashTable H = malloc(sizeof(struct HTable));
    H->TableSize = getNextPrime(N);
    H->TheCells = malloc(H->TableSize * sizeof(Cell));
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheCells[i] = malloc(sizeof(struct CellNode));
        H->TheCells[i]->Data = NULL;
        H->TheCells[i]->Cnt = 0;
    }
    return H;
}

long Find(HashTable H, char *Elem)
{
    long Cnt = 0;
    long NewPos = Hash(Elem, H->TableSize);
    long CurrPos = NewPos;
    while (H->TheCells[NewPos]->Data != NULL &&
        StrCmp(H->TheCells[NewPos]->Data, Elem) != 0)
    {
        if (++Cnt % 2)
        {
            NewPos = CurrPos + (Cnt + 1) / 2 * (Cnt + 1) / 2;
            while (NewPos >= H->TableSize)
            {
                NewPos -= H->TableSize;
            }
        }
        else
        {
            NewPos = CurrPos - (Cnt / 2) * (Cnt / 2);
            while (NewPos < 0)
            {
                NewPos += H->TableSize;
            }
        }
    }
    return NewPos;
}

void Insert(HashTable H, char *Elem, long *MaxCnt, long *MaxIndex, long *MaxIndex)
{
    long NewPos = Find(H, Elem);
    if (H->TheCells[NewPos]->Data == NULL)
    {
        char *Data = malloc(LENGTH * sizeof(char));
        strcpy(Data, Elem);
        H->TheCells[NewPos]->Data = Data;
        H->TheCells[NewPos]->Cnt += 1;
    }
    else
    {
        H->TheCells[NewPos]->Cnt += 1;
        Cnt = H->TheCells[NewPos]->Cnt;
        Tel = H->TheCells[NewPos]->Data;
        if (Cnt != 0 &&
            (Cnt > *MaxCnt ||
            (Cnt == *MaxCnt && (StrCmp(Tel, H->TheCells[MaxIndex]->Data) == 1))))
        {
            MaxCnt = Cnt;
            MaxIndex = i;
        }
    }
}


long Hash(char *Data, long N)
{
    return atoi(Data+11-5) % N;
}

long getNextPrime(long N)
{
    long K = (2 * N - 3) / 4;
    while (4 * K + 3 < 3 * N || !IsPrime(4 * K + 3))
    {
        K++;
    }
    return 4 * K + 3;
}

bool IsPrime(long N)
{
    long i;
    bool IsTrue = true;
    for (i = 2; i*i <= N; ++i)
    {
        if (N % i == 0)
        {
            IsTrue = false;
        }
    }
    return IsTrue;
}



