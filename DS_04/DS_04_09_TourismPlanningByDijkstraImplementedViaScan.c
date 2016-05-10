/*
* Data Structures in C
* Tourism Planning By Dijkstra (AdjacencyList) Implemented Via Scan
* LuoYingYing
* 20160508
*/



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxNum 25000

typedef struct VNode *Vertex;
struct VNode
{
    int ID;
    int WeightOfDistance;
    int WeightOfPrice;
    Vertex Next;
};

void ReadEdge2Graph(Vertex* AdjacencyList, int NumOfVertexes, int NumOfEdges);
void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, int WeightOfDistance, int WeightOfPrice);
void Insert2AdjacencyList(Vertex VertexNode, int VertexID, int WeightOfDistance, int WeightOfPrice);
void Dijkstra(Vertex *AdjacencyList, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int N);
void Initialization(Vertex *AdjacencyList, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int ID, int N);

int main(int argc, char const *argv[])
{
    int N, M, S, D;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    Vertex *AdjacencyList = (Vertex*)malloc(N * sizeof(Vertex));
    long *WeightsOfDistance = (long*)malloc(N * sizeof(long));
    long *WeightsOfPrice = (long*)malloc(N * sizeof(long));
    bool *Collected = (bool*)malloc(N * sizeof(bool));
    ReadEdge2Graph(AdjacencyList, N, M);
    Initialization(AdjacencyList, WeightsOfDistance, WeightsOfPrice, Collected, S, N);
    Dijkstra(AdjacencyList, WeightsOfDistance, WeightsOfPrice, Collected, N);
    printf("%d %d\n", WeightsOfDistance[D], WeightsOfPrice[D]);
    return 0;
}

void ReadEdge2Graph(Vertex* AdjacencyList, int NumOfVertexes, int NumOfEdges)
{
    int i;
    for (i = 0; i < NumOfVertexes; ++i)
    {
        AdjacencyList[i] = (Vertex)malloc(sizeof(struct VNode));
        AdjacencyList[i]->ID = i;
        AdjacencyList[i]->WeightOfDistance = AdjacencyList[i]->WeightOfPrice = 0;
        AdjacencyList[i]->Next = NULL;
    }
    for (i = 0; i < NumOfEdges; ++i)
    {
        int VertexID1, VertexID2;
        int WeightOfDistance, WeightOfPrice;
        scanf("%d %d %d %d", &VertexID1, &VertexID2, &WeightOfDistance, &WeightOfPrice);
        SetEdge(AdjacencyList, VertexID1, VertexID2, WeightOfDistance, WeightOfPrice);
    }
}

void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, int WeightOfDistance, int WeightOfPrice)
{
    Insert2AdjacencyList(AdjacencyList[VertexID1], VertexID2, WeightOfDistance, WeightOfPrice);
    Insert2AdjacencyList(AdjacencyList[VertexID2], VertexID1, WeightOfDistance, WeightOfPrice);
}

void Insert2AdjacencyList(Vertex VertexNode, int VertexID, int WeightOfDistance, int WeightOfPrice)
{
    if (!VertexNode->Next || VertexNode->Next->ID >= VertexID)
    {
        Vertex TempVertex = (Vertex)malloc(sizeof(struct VNode));
        TempVertex->ID = VertexID;
        TempVertex->WeightOfDistance = WeightOfDistance;
        TempVertex->WeightOfPrice = WeightOfPrice;
        TempVertex->Next = VertexNode->Next ? VertexNode->Next : NULL;
        VertexNode->Next = TempVertex;
    }
    else
    {
        Insert2AdjacencyList(VertexNode->Next, VertexID, WeightOfDistance, WeightOfPrice);
    }
}

void Initialization(Vertex *AdjacencyList, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int ID, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        WeightsOfDistance[i] = MaxNum;
        WeightsOfPrice[i] = MaxNum;
        Collected[i] = false;
    }
    WeightsOfDistance[ID] = WeightsOfPrice[ID] = 0;
    Vertex V = AdjacencyList[ID];
    while(V->Next)
    {
        V = V->Next;
        WeightsOfDistance[V->ID] = V->WeightOfDistance;
        WeightsOfPrice[V->ID] = V->WeightOfPrice;
    }
}


void Dijkstra(Vertex *AdjacencyList, long *WeightsOfDistance, long *WeightsOfPrice, bool *Collected, int N)
{
    while (1)
    {
        int FatherID = FindMin(WeightsOfDistance, Collected, N);
        if (FatherID == -1) break;
        Vertex V = AdjacencyList[FatherID];
        Collected[FatherID] = true;
        while (V->Next)
        {
            V = V->Next;
            int ID = V->ID, WD = V->WeightOfDistance, WP = V->WeightOfPrice;
            if ( Collected[ID] == false &&
                (WeightsOfDistance[ID] > WD + WeightsOfDistance[FatherID] ||
                (WeightsOfDistance[ID] == WD + WeightsOfDistance[FatherID] &&
                    WeightsOfPrice[ID] > WP + WeightsOfPrice[FatherID]) ) )
            {
                WeightsOfDistance[ID] = WD + WeightsOfDistance[FatherID];
                WeightsOfPrice[ID] = WP + WeightsOfPrice[FatherID];
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

