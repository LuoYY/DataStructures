/*
* Data Structures in C
* Radix Sort
* LuoYingYing
* 20160516
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s

typedef struct Node *BNode;
struct Node
{
    int Data;
    BNode Next;
};

int Sum(int S[], int N);
void Insert2Bucket(BNode *P, BNode *Tail, int Elem);

int main(int argc, char const *argv[])
{
    int N, K;
    long M, i, j;
    scanf("%d %d %ld", &N, &K, &M);
    int *FullMarkOfProblems = malloc(K * sizeof(int));
    int **RecordsOfUser = malloc(N * sizeof(int*));
    for (i = 0; i < N; i++)
    {
        RecordsOfUser[i] = malloc((K + 3) * sizeof(int*));
        RecordsOfUser[i][0] = 0;   /* Num of the submittion can pass the compiler */
        for (j = 1; j < K + 1; j++)
        {
            RecordsOfUser[i][j] = -2;
        }
        RecordsOfUser[i][K + 1] = 0; /* Total score of user solved problems */
        RecordsOfUser[i][K + 2] = 0; /* Num of perfectly solved problems */
    }

    for (i = 0; i < K; i++)
    {
        scanf("%d", &FullMarkOfProblems[i]);
    }

    for (i = 0; i < M; i++)
    {
        int UserID, ProblemID, Score;
        scanf("%d %d %d", &UserID, &ProblemID, &Score);
        UserID -= 1;
        if (Score >= -1)
        {
            if (Score > -1) RecordsOfUser[UserID][0] += 1;
            if (FullMarkOfProblems[ProblemID - 1] == Score && RecordsOfUser[UserID][ProblemID] != FullMarkOfProblems[ProblemID - 1])
            {
                RecordsOfUser[UserID][K + 2] += 1;
            }
            if (Score > RecordsOfUser[UserID][ProblemID])
            {
                RecordsOfUser[UserID][ProblemID] = RecordsOfUser[UserID][ProblemID] == -2 ? 0 : RecordsOfUser[UserID][ProblemID];
                Score = Score == -1 ? 0 : Score;
                RecordsOfUser[UserID][K + 1] += Score - RecordsOfUser[UserID][ProblemID];
                RecordsOfUser[UserID][ProblemID] = Score;
            }
        }
    }

    int SumOfScore = Sum(FullMarkOfProblems, K);
    BNode *Buckets1 = malloc((K + 1) * sizeof(BNode));
    BNode *Buckets1Tail = malloc((K + 1) * sizeof(BNode));
    BNode *Buckets2 = malloc((SumOfScore + 1) * sizeof(BNode));
    BNode *Buckets2Tail = malloc((SumOfScore + 1) * sizeof(BNode));
    BNode Tmp;
    int Cnt = 1, Cnt4Print;
    for (i = 0; i < K + 1; ++i)
    {
        Buckets1Tail[i] = Buckets1[i] = NULL;
    }
    for (i = 0; i < N; i++)
    {
        if (RecordsOfUser[i][0] > 0)
        {
            int t = RecordsOfUser[i][K + 2];
            Insert2Bucket(&Buckets1[t], &Buckets1Tail[t], i);
        }
    }
    for (i = 0; i < SumOfScore + 1; i++)
    {
        Buckets2Tail[i] = Buckets2[i] = NULL;
    }
    for (i = K; i >= 0; i--)
    {
        Tmp = Buckets1[i];
        while (Tmp != NULL)
        {
            int t = RecordsOfUser[Tmp->Data][K + 1];
            Insert2Bucket(&Buckets2[t], &Buckets2Tail[t], Tmp->Data);
            Tmp = Tmp->Next;
        }
    }
    for (i = SumOfScore; i >= 0; i--)
    {
        Tmp = Buckets2[i];
        if (Tmp != NULL)
        {
            Cnt4Print = Cnt;
            while (Tmp != NULL)
            {
                printf("%d %05d %d", Cnt4Print, Tmp->Data + 1, RecordsOfUser[Tmp->Data][K + 1]);
                for (j = 1; j < K + 1; j++)
                {
                    if (RecordsOfUser[Tmp->Data][j] == -2)
                    {
                        printf(" -");
                    }
                    else
                    {
                        printf(" %d", RecordsOfUser[Tmp->Data][j]);
                    }
                }
                printf("\n");
                Tmp = Tmp->Next;
                Cnt++;
            }
        }
    }
    return 0;
}

int Sum(int S[], int N)
{
    int i, sum = 0;
    for (i = 0; i < N; ++i)
    {
        sum += S[i];
    }
    return sum;
}

void Insert2Bucket(BNode *P, BNode *Tail, int Elem)
{
    BNode NewNode = malloc(sizeof(struct Node));
    NewNode->Data = Elem;
    NewNode->Next = NULL;
    if (*P == NULL)
    {
        *P = NewNode;
    }
    else
    {
        (*Tail)->Next = NewNode;
    }
    *Tail = NewNode;
}
