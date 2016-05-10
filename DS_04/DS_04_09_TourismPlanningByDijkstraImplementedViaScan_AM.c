/*
* Data Structures in C
* Tourism Planning By Dijkstra (AdjacencyMatrix) Implemented Via Scan
* LuoYingYing
* 20160508
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxNum 250000

void ReadEdge2Graph(int **Distances, int **Prices, int NumOfVertexes, int NumOfEdges);
void Initialization(int **Distances, int **Prices, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int ID, int N);
void Dijkstra(int **Distances, int **Prices, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int N);
int FindMin(long *WeightsOfDistance, bool *Collected, int N);

int main(int argc, char const *argv[])
{
    int N, M, S, D;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    int **Distances = (int**)malloc(N * sizeof(int*));
    int **Prices = (int**)malloc(N * sizeof(int*));
    long *WeightsOfDistance = (long*)malloc(N * sizeof(long));
    long *WeightsOfPrice = (long*)malloc(N * sizeof(long));
    bool *Collected = (bool*)malloc(N * sizeof(bool));
    ReadEdge2Graph(Distances, Prices, N, M);
    Initialization(Distances, Prices, WeightsOfDistance, WeightsOfPrice, Collected, S, N);
    Dijkstra(Distances, Prices, WeightsOfDistance, WeightsOfPrice, Collected, N);
    printf("%d %d\n", WeightsOfDistance[D], WeightsOfPrice[D]);
    return 0;
}

void ReadEdge2Graph(int **Distances, int **Prices, int NumOfVertexes, int NumOfEdges)
{
    int i, j;
    for (i = 0; i < NumOfVertexes; ++i)
    {
        Distances[i] = (int*)malloc((NumOfVertexes) * sizeof(int));
        Prices[i] = (int*)malloc((NumOfVertexes) * sizeof(int));
        for (j = 0; j < NumOfVertexes; ++j)
        {
            if (i == j)
            {
                Prices[i][j] = 0;
                Distances[i][j] = 0;
            }
            else
            {
                Prices[i][j] = -1;
                Distances[i][j] = -1;
            }
        }
    }
    for (i = 0; i < NumOfEdges; ++i)
    {
        int VertexID1, VertexID2;
        int WeightOfDistance, WeightOfPrice;
        scanf("%d %d %d %d", &VertexID1, &VertexID2, &WeightOfDistance, &WeightOfPrice);
        Prices[VertexID1][VertexID2] = Prices[VertexID2][VertexID1] = WeightOfPrice;
        Distances[VertexID1][VertexID2] = Distances[VertexID2][VertexID1] = WeightOfDistance;
    }
}

void Initialization(int **Distances, int **Prices, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int ID, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        WeightsOfDistance[i] = MaxNum;
        WeightsOfPrice[i] = MaxNum;
        Collected[i] = false;
    }
    WeightsOfDistance[ID] = WeightsOfPrice[ID] = 0;
    for ( i = 0; i < N; ++i)
    {
        if (i != ID && Distances[ID][i] != -1)
        {
            WeightsOfDistance[i] = Distances[ID][i];
            WeightsOfPrice[i] = Prices[ID][i];
        }
    }
}


void Dijkstra(int **Distances, int **Prices, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int N)
{
    while (1)
    {
        int i;
        int FatherID = FindMin(WeightsOfDistance, Collected, N);
        if (FatherID == -1) break;
        Collected[FatherID] = true;
        for (i = 0; i < N; ++i)
        {
            int WD = Distances[FatherID][i], WP = Prices[FatherID][i];
            if (WD != -1)
            {
                if ( Collected[i] == false &&
                    (WeightsOfDistance[i] > WD + WeightsOfDistance[FatherID] ||
                    (WeightsOfDistance[i] == WD + WeightsOfDistance[FatherID] &&
                        WeightsOfPrice[i] > WP + WeightsOfPrice[FatherID]) ) )
                {
                    WeightsOfDistance[i] = WD + WeightsOfDistance[FatherID];
                    WeightsOfPrice[i] = WP + WeightsOfPrice[FatherID];
                }
            }
        }
    }
}

int FindMin(long *WeightsOfDistance, bool *Collected, int N)
{
    int i, index = -1;
    long minNum = MaxNum;
    for (i = 0; i < N; ++i)
    {
        if ( !Collected[i] && WeightsOfDistance[i] < minNum)
        {
            minNum = WeightsOfDistance[i];
            index = i;
        }
    }
    return index;
}

