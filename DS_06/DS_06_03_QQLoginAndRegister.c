/*
* Data Structures in C
* QQ Login and Register
* LuoYingYing
* 20160520
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define LENGTH1 11
#define LENGTH2 17

typedef struct HTable *HashTable;
typedef struct CellNode *Cell;

struct HTable
{
    int TableSize;
    Cell *TheCells;
};

struct CellNode
{
    char* ID; //10
    char* PWD;//16
    Cell Next;
};

HashTable CreateHashTable(long N);
long Hash(char *ID, long N);
long GetNextPrime( long N );
Cell Find(HashTable H, char *Elem);
void Handle(HashTable H, char OP, char *ID, char *PWD);

int main(int argc, char const *argv[])
{
    int N, i;
    char OP, Enter;
    char *ID, *PWD;
    ID = malloc(LENGTH1 * sizeof(char));
    PWD = malloc(LENGTH2 * sizeof(char));
    scanf("%d", &N);
    HashTable H = CreateHashTable(2*N); 
    for (i = 0; i < N; i++)
    {
        scanf("%c", &Enter);
        scanf("%c %s %s", &OP, ID, PWD);
        Handle(H, OP, ID, PWD);
    }
    return 0;
}

HashTable CreateHashTable(long N)
{
    long i;
    HashTable H = malloc(sizeof(struct HTable));
    H->TableSize = GetNextPrime(N);
    H->TheCells = malloc(H->TableSize * sizeof(Cell));
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheCells[i] = malloc(sizeof(struct CellNode));
        H->TheCells[i]->ID = NULL;
        H->TheCells[i]->PWD = NULL;
        H->TheCells[i]->Next = NULL;
    }
    return H;
}


void Handle(HashTable H, char OP, char *ID, char *PWD)
{
    Cell NewPos = Find(H, ID);
    if (NewPos == NULL)
    {
        if (OP == 'L')
        {
            printf("ERROR: Not Exist\n");
        }
        else
        {
            Cell Head = H->TheCells[Hash(ID, H->TableSize)];
            Cell Tmp = malloc(sizeof(struct CellNode));
            Tmp->ID = malloc(LENGTH1 * sizeof(char));
            Tmp->PWD = malloc(LENGTH2 * sizeof(char));
            Tmp->Next = Head->Next;
            Head->Next = Tmp;
            strcpy(Tmp->ID, ID);
            strcpy(Tmp->PWD, PWD);
            printf("New: OK\n");
        }
    }
    else
    {
        if (OP == 'N')
        {
            printf("ERROR: Exist\n");
        }
        else
        {
            if(strcmp(NewPos->PWD, PWD) == 0)
            {
                printf("Login: OK\n");
            }
            else
            {
                printf("ERROR: Wrong PW\n");
            }
        }
    }
}

Cell Find(HashTable H, char *Elem)
{
    Cell NewPos;
    long index = Hash(Elem, H->TableSize);
    NewPos = H->TheCells[index]->Next;
    while (NewPos != NULL && strcmp(NewPos->ID, Elem) != 0)
    {
        NewPos = NewPos->Next;
    }
    return NewPos;
}

long Hash(char *ID, long N)
{
    long i, sum = 0;
    for (i = 0; i < 5 && ID[i] != '\0'; i++)
    {
        sum = sum*10 + ID[i];
    }
    while( sum < 10000)
    {
        sum *= 10;
    }
    return sum % N;
}

long GetNextPrime( long N )
{
    long i, p = ( N%2 ) ? N+2: N+1;
    while ( p<= 1000000 ) {
        for( i = (long)sqrt(p); i>2; i-- )
            if( !(p%i) ) break;
        if( i==2 ) break;
        else p += 2;
    }
    return p;
}

