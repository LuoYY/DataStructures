/*
* Data Structures in C
* Every village access roads problem 
* Solved by prim 
* LuoYingYing
* 20160510
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxNum 2000
#define scanf scanf_s

void ReadData2Graph(int **Distances, int NumOfVertexes, int NumOfEdges);
void Initialization(int **Distances, int *WeightsOfDistance, int *Parent, int RootID, int N);
void Prim(int **Distances, int *WeightsOfDistance, int *Parent, int N);
int FindMin(int *WeightsOfDistance, int N);
int CalcTotalDistance(int **Distances, int *Parent, int N);
void printN(int *Parent, int N);

int main(int argc, char const *argv[])
{
    int N, M;
    scanf("%d %d", &N, &M);
    int **Distances = (int**)malloc(N * sizeof(int*));
    int *WeightsOfDistance = (int*)malloc(N * sizeof(int));
    int *Parent = (int*)malloc(N * sizeof(bool));
    ReadData2Graph(Distances, N, M);
    Initialization(Distances, WeightsOfDistance, Parent, 0, N); printN(Parent, N);
    Prim(Distances, WeightsOfDistance, Parent, N); printN(Parent, N);
    printf("%d\n", CalcTotalDistance(Distances, Parent, N));
    return 0;
}

void printN(int *Parent, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        printf(" %d", Parent[i]);
    }
    printf("\n");
}

void ReadData2Graph(int **Distances, int NumOfVertexes, int NumOfEdges)
{
    int i, j;
    for (i = 0; i < NumOfVertexes; ++i)
    {
        Distances[i] = (int*)malloc((NumOfVertexes) * sizeof(int));
        for (j = 0; j < NumOfVertexes; ++j)
        {
            if (i == j)
            {
                Distances[i][j] = 0;
            }
            else
            {
                Distances[i][j] = -1;
            }
        }
    }
    for (i = 0; i < NumOfEdges; ++i)
    {
        int VertexID1, VertexID2;
        int WeightOfDistance;
        scanf("%d %d %d", &VertexID1, &VertexID2, &WeightOfDistance);
        Distances[VertexID1-1][VertexID2-1] = Distances[VertexID2 - 1][VertexID1 - 1] = WeightOfDistance;
    }
}

void Initialization(int **Distances, int *WeightsOfDistance, int *Parent, int RootID, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        WeightsOfDistance[i] = -1;
        Parent[i] = -1;
    }
    WeightsOfDistance[RootID] = 0;
    for (i = 0; i < N; ++i)
    {
        if (i != RootID && Distances[RootID][i] != -1)
        {
            WeightsOfDistance[i] = Distances[RootID][i];
            Parent[i] = RootID;
        }
    }
}

void Prim(int **Distances, int *WeightsOfDistance, int *Parent, int N)
{
    int i, D, WOD;
    int FatherID;
    while (1)
    {
        FatherID = FindMin(WeightsOfDistance, N);
        WeightsOfDistance[FatherID] = 0;
        if (FatherID == -1) break;
        for (i = 0; i < N; ++i)
        {
            D = Distances[FatherID][i];
            WOD = WeightsOfDistance[i];
            if (D != -1)
            {
                if (WOD != 0 && (WOD == -1 || WOD > D))
                {
                    WeightsOfDistance[i] = D;
                    Parent[i] = FatherID;
                    printN(Parent, N);
                }
            }
        }
    }
}

int FindMin(int *WeightsOfDistance, int N)
{
    int i, WOD, index = -1;
    int minNum = MaxNum;
    for (i = 0; i < N; ++i)
    {
        WOD = WeightsOfDistance[i];
        if (WOD != 0 && WOD != -1 && WOD < minNum)
        {
            minNum = WOD;
            index = i;
        }
    }
    return index;
}

int CalcTotalDistance(int **Distances, int *Parent, int N)
{
    int i, sum = 0, cnt = 0;
    for (i = 0; i < N; ++i)
    {
        if (Parent[i] == -1)
        {
            cnt++;
        }
        else
        {
            sum += Distances[i][Parent[i]];
        }
    }
    if (cnt != 1)
    {
        sum = -1;
    }
    return sum;
}