/*
* Data Structures in C
* Tourism Planning By DFS
* LuoYingYing
* 20160508
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
void DFS(Vertex V, Vertex *AdjacencyList, int *WeightsOfDistance, int *WeightsOfPrice);
void ResetWeights(int *Weights, int N);

int main(int argc, char const *argv[])
{
    int N, M, S, D;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    Vertex *AdjacencyList = (Vertex*)malloc(N * sizeof(Vertex));
    int *WeightsOfDistance = (int*)malloc(N * sizeof(int));
    int *WeightsOfPrice = (int*)malloc(N * sizeof(int));
    ReadEdge2Graph(AdjacencyList, N, M);
    ResetWeights(WeightsOfDistance, N);
    ResetWeights(WeightsOfPrice, N);
    WeightsOfDistance[S] = WeightsOfPrice[S] = 0;
    DFS(AdjacencyList[S], AdjacencyList, WeightsOfDistance, WeightsOfPrice);
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


void DFS(Vertex V, Vertex *AdjacencyList, int *WeightsOfDistance, int *WeightsOfPrice)
{
    int FatherID = V->ID;
    while (V->Next)
    {
        V = V->Next;
        int ID = V->ID, WD = V->WeightOfDistance, WP = V->WeightOfPrice;
        if ( WeightsOfDistance[ID] == -1 ||
            WeightsOfDistance[ID] > WD + WeightsOfDistance[FatherID] ||
            (WeightsOfDistance[ID] == WD + WeightsOfDistance[FatherID] &&
                WeightsOfPrice[ID] > WP + WeightsOfPrice[FatherID]) )
        {
            WeightsOfDistance[ID] = WD + WeightsOfDistance[FatherID];
            WeightsOfPrice[ID] = WP + WeightsOfPrice[FatherID];
            DFS(AdjacencyList[ID], AdjacencyList, WeightsOfDistance, WeightsOfPrice);
        }
    }
}

void ResetWeights(int *Weights, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        Weights[i] = -1;
    }
}
