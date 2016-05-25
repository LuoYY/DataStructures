/*
* Data Structures in C
* Hashing
* LuoYingYing
* 20160520
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define scanf scanf_s

typedef struct HTable *HashTable;
typedef int Cell;

struct HTable
{
    int TableSize;
    Cell *TheCells;
};


HashTable CreateHashTable(int N);
void Insert(HashTable H, int Elem, int *Position);
int Find(HashTable H, int Elem);
int Hash(int key, int N);
int GetNextPrime(int N);
bool IsPrime(int N);
void printResult(int *Positions, int N);

int main(int argc, char const *argv[])
{
    int N, M, i, Elem;
    scanf("%d %d", &M, &N);
    HashTable H = CreateHashTable(M);
    int *Pos = malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
    {
        scanf("%d", &Elem);
        Insert(H, Elem, &Pos[i]);
    }
    printResult(Pos, N);
    return 0;
}

void printResult(int *Positions, int N)
{
    int i;
    bool IsFirst = true;
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
        if (Positions[i] == -1)
        {
            printf("-");
        }
        else
        {
            printf("%d", Positions[i]);
        }
    }
}

HashTable CreateHashTable(int N)
{
    int i;
    HashTable H = malloc(sizeof(struct HTable));
    H->TableSize = GetNextPrime(N);
    H->TheCells = malloc(H->TableSize * sizeof(Cell));
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheCells[i] = -1;
    }
    return H;
}

int Find(HashTable H, int Elem)
{
    int Cnt = 0;
    int NewPos = Hash(Elem, H->TableSize);
    int CurrPos = NewPos;
    while ( H->TheCells[NewPos] != -1 && Cnt < H->TableSize)
    {
        Cnt++;
        NewPos = (CurrPos + Cnt * Cnt) % H->TableSize;
    }
    if ( Cnt >= H->TableSize )
    {
        NewPos = -1;
    }
    return NewPos;
}

void Insert(HashTable H, int Elem, int *Position)
{
    int NewPos = Find(H, Elem);
    *Position = NewPos;
    if (NewPos != -1)
    {
        H->TheCells[NewPos] = Elem;
    }
}


int Hash(int key, int N)
{
    return key % N;
}

int GetNextPrime(int N)
{
    if (N > 2)
    {
        N = (N % 2) ? N : N + 1;
    }
    else
    {
        N = 2;
    }
    while (!IsPrime(N))
    {
        N += 2;
    }
    return N;
}

bool IsPrime(int N)
{
    int i;
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