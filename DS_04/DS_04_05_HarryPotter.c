/*
* Data Structures in C
* Harry Potter Examination.
* LuoYingYing
* 20160506
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* #define scanf scanf_s */

typedef struct VNode *Vertex;
struct VNode
{
    int ID;
    int Weight;
    Vertex Next;
};

typedef struct LinkQueue *VertexQueue;

typedef struct Node
{
    Vertex Data;
    struct Node *Next;
}QNode;

struct LinkQueue
{
    QNode *Rear;
    QNode *Front;
};

Vertex* CreateGraph(int NumOfVertexes);
void ReadEdge2Graph(Vertex* AdjacencyList, int NumOfEdges);
void JudgeGraph(Vertex* AdjacencyList, int NumOfVertexes);
void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, int Weight);
void Insert2AdjacencyList(Vertex VertexNode, int VertexID, int Weight);
void BFS(Vertex V, Vertex *AdjacencyList, int *WeightOfVertexes, int N);
void ResetWeightOfVertexes(int *WeightOfVertexes, int N);
int CountWeightOfVertexes(int *WeightOfVertexes, int N);
bool IsEmpty(VertexQueue VQ);
void Add2Queue(VertexQueue VQ, Vertex V);
Vertex DeleteQ(VertexQueue VQ);
VertexQueue CreateQueue();
void printS(int *S, int N);

int main(int argc, char const *argv[])
{
    int NumOfAnimals, NumOfEdges;
    scanf("%d %d", &NumOfAnimals, &NumOfEdges);
    Vertex *AdjacencyList = CreateGraph(NumOfAnimals);
    ReadEdge2Graph(AdjacencyList, NumOfEdges);
    JudgeGraph(AdjacencyList, NumOfAnimals);
    return 0;
}

void JudgeGraph(Vertex* AdjacencyList, int NumOfVertexes)
{
    bool exist = false;
    int VertexMaxWeight, MaxWeight = 10001, index = 0, i;
    int *WeightOfVertexes = (int*)malloc(NumOfVertexes * sizeof(int));
    for (i = 0; i < NumOfVertexes; ++i)
    {
        ResetWeightOfVertexes(WeightOfVertexes, NumOfVertexes);
        BFS(AdjacencyList[i], AdjacencyList, WeightOfVertexes, NumOfVertexes);
        VertexMaxWeight = CountWeightOfVertexes(WeightOfVertexes, NumOfVertexes);
        if (VertexMaxWeight != -1 && VertexMaxWeight < MaxWeight)
        {
            index = i;
            MaxWeight = VertexMaxWeight;
            exist = true;
        }
    }
    exist ? printf("%d %d\n", index+1, MaxWeight) : printf("0\n");
}

Vertex* CreateGraph(int NumOfVertexes)
{
    int i;
    Vertex *AdjacencyList = (Vertex*)malloc(NumOfVertexes * sizeof(struct VNode));
    for (i = 0; i < NumOfVertexes; ++i)
    {
        AdjacencyList[i] = (Vertex)malloc(sizeof(struct VNode));
        AdjacencyList[i]->ID = i;
        AdjacencyList[i]->Weight = 0;
        AdjacencyList[i]->Next = NULL;
    }
    return AdjacencyList;
}

void ReadEdge2Graph(Vertex* AdjacencyList, int NumOfEdges)
{
    int i;
    for (i = 0; i < NumOfEdges; ++i)
    {
        int VertexID1, VertexID2, Weight;
        scanf("%d %d %d", &VertexID1, &VertexID2, &Weight);
        SetEdge(AdjacencyList, VertexID1 - 1, VertexID2 - 1, Weight);
    }
}

void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, int Weight)
{
    Insert2AdjacencyList(AdjacencyList[VertexID1], VertexID2, Weight);
    Insert2AdjacencyList(AdjacencyList[VertexID2], VertexID1, Weight);
}

void Insert2AdjacencyList(Vertex VertexNode, int VertexID, int Weight)
{
    if (!VertexNode->Next || VertexNode->Next->ID >= VertexID)
    {
        Vertex TempVertex = (Vertex)malloc(sizeof(struct VNode));
        TempVertex->ID = VertexID;
        TempVertex->Weight = Weight;
        TempVertex->Next = VertexNode->Next ? VertexNode->Next : NULL;
        VertexNode->Next = TempVertex;
    }
    else
    {
        Insert2AdjacencyList(VertexNode->Next, VertexID, Weight);
    }
}

void BFS(Vertex V, Vertex *AdjacencyList, int *WeightOfVertexes, int N)
{
    VertexQueue VQ = CreateQueue();
    WeightOfVertexes[V->ID] = 0;
    Add2Queue(VQ, V);
    while (!IsEmpty(VQ))
    {
        //printS(WeightOfVertexes, N);
        Vertex TempVertex = DeleteQ(VQ);
        int FatherWeight = WeightOfVertexes[TempVertex->ID];
        while (TempVertex->Next)
        {
            TempVertex = TempVertex->Next;
            int ID = TempVertex->ID, Weight = TempVertex->Weight;
            if (WeightOfVertexes[ID] == -1 || WeightOfVertexes[ID] > FatherWeight + Weight)
            {
                WeightOfVertexes[ID] = FatherWeight + Weight;
                //printS(WeightOfVertexes, N);
                Add2Queue(VQ, AdjacencyList[ID]);
            }
        }
    }
}

void printS(int *S, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        printf(" %d", S[i]);
    }
    printf("\n");
}

void ResetWeightOfVertexes(int *WeightOfVertexes, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        WeightOfVertexes[i] = -1;
    }
}

int CountWeightOfVertexes(int *WeightOfVertexes, int N)
{
    int i, cnt = 0, Max = -1;
    for (i = 0; i < N; ++i)
    {
        int tmp = WeightOfVertexes[i];
        if (tmp > -1)
        {
            cnt++;
            if (tmp > Max)
            {
                Max = tmp;
            }
        }
        else
        {
            break;
        }
    }
    return cnt == N ? Max : -1;
}

VertexQueue CreateQueue()
{
    VertexQueue VQ = (VertexQueue)malloc(sizeof(struct LinkQueue));
    VQ->Rear = NULL;
    VQ->Front = NULL;
    return VQ;
}

bool IsEmpty(VertexQueue VQ)
{
    return VQ->Front == NULL;
}

void Add2Queue(VertexQueue VQ, Vertex V)
{
    QNode *temp = (QNode*)malloc(sizeof(QNode));
    temp->Data = V;
    temp->Next = NULL;
    if (VQ->Front == NULL)
    {
        VQ->Front = temp;
    }
    else
    {
        VQ->Rear->Next = temp;
    }
    VQ->Rear = temp;
}

Vertex DeleteQ(VertexQueue VQ)
{
    if (!IsEmpty(VQ))
    {
        QNode *temp = VQ->Front;
        Vertex V = temp->Data;
        VQ->Front = VQ->Front->Next;
        free(temp);
        return V;
    }
}