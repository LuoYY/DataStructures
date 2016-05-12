/*
* Data Structures in C
* Saving James Bond - Easy Version.
* LuoYingYing
* 20160502
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* #define scanf scanf_s */

typedef struct VNode *Vertex;
struct VNode
{
    int ID;
    Vertex Next;
};

typedef struct PointNode *Point;
struct PointNode
{
    int X;
    int Y;
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

void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2);
void Insert2List(Vertex VertexNode, int VertexID);
bool CanFirstJump(Point P, int D);
bool CanJump2Land(Point P, int D);
bool CanJump(Point P1, Point P2, int D);
void ResetVertexVisited(bool *VertexVisited, int N);
bool BFS(Vertex V, Vertex *AdjacencyList, bool *VertexVisited, int KeyID);
bool IsEmpty(VertexQueue VQ);
void Add2Queue(VertexQueue VQ, Vertex V);
Vertex DeleteQ(VertexQueue VQ);
VertexQueue CreateQueue();

int main(int argc, char const *argv[])
{
    int i, j;
    int NumOfVertex, LimitOfDistance;
    bool HaveSafe = false;
    scanf("%d %d", &NumOfVertex, &LimitOfDistance);
    NumOfVertex = NumOfVertex + 2;
    bool *VertexVisited = (bool*)malloc(NumOfVertex * sizeof(bool));
    Vertex *AdjacencyList = (Vertex*)malloc(NumOfVertex * sizeof(Vertex));
    Point *Points = (Point*)malloc(NumOfVertex * sizeof(Point));

    AdjacencyList[0] = (Vertex)malloc(sizeof(struct VNode));
    AdjacencyList[NumOfVertex - 1] = (Vertex)malloc(sizeof(struct VNode));
    AdjacencyList[0]->ID = 0;
    AdjacencyList[NumOfVertex - 1]->ID = NumOfVertex - 1;
    AdjacencyList[0]->Next = AdjacencyList[NumOfVertex - 1]->Next = NULL;

    if (15/2.0 + LimitOfDistance >= 50)
    {
        HaveSafe = true;
    }
    else
    {
        for (i = 1; i <= NumOfVertex - 2; ++i)
        {
            Points[i] = (Point)malloc(NumOfVertex * sizeof(struct PointNode));
            scanf("%d %d", &(Points[i]->X), &(Points[i]->Y));
            AdjacencyList[i] = (Vertex)malloc(sizeof(struct VNode));
            AdjacencyList[i]->ID = i;
            AdjacencyList[i]->Next = NULL;
            if (CanFirstJump(Points[i], LimitOfDistance))
            {
                SetEdge(AdjacencyList, 0, i);
            }
            if (CanJump2Land(Points[i], LimitOfDistance))
            {
                SetEdge(AdjacencyList, NumOfVertex - 1, i);
            }
        }

        for (i = 1; i <= NumOfVertex - 2; ++i)
        {
            for (j = i; j <= NumOfVertex - 2; ++j)
            {
                if (i != j && CanJump(Points[i], Points[j], LimitOfDistance))
                {
                    SetEdge(AdjacencyList, i, j);
                }
            }
        }
        ResetVertexVisited(VertexVisited, NumOfVertex);
        HaveSafe = BFS(AdjacencyList[0], AdjacencyList, VertexVisited, NumOfVertex - 1);
    }
    printf("%s\n", HaveSafe ? "Yes" : "No");
    return 0;
}

void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2)
{
    Insert2List(AdjacencyList[VertexID1], VertexID2);
    Insert2List(AdjacencyList[VertexID2], VertexID1);
}


void Insert2List(Vertex VertexNode, int VertexID)
{
    if (!VertexNode->Next || VertexNode->Next->ID >= VertexID)
    {
        Vertex TempVertex = (Vertex)malloc(sizeof(struct VNode));
        TempVertex->ID = VertexID;
        TempVertex->Next = VertexNode->Next ? VertexNode->Next : NULL;
        VertexNode->Next = TempVertex;
    }
    else
    {
        Insert2List(VertexNode->Next, VertexID);
    }
}

bool CanFirstJump(Point P, int D)
{
    return (P->X)*(P->X) + (P->Y)*(P->Y) < (15 / 2.0 + D) * (15 / 2.0 + D);
}

bool CanJump2Land(Point P, int D)
{
    return P->X <= -50 + D || P->X >= 50 - D || P->Y <= -50 + D || P->Y >= 50 - D;
}

bool CanJump(Point P1, Point P2, int D)
{
    return (P1->X - P2->X)*(P1->X - P2->X) + (P1->Y - P2->Y)*(P1->Y - P2->Y) < D * D;
}

void ResetVertexVisited(bool *VertexVisited, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        VertexVisited[i] = false;
    }
}

bool BFS(Vertex V, Vertex *AdjacencyList, bool *VertexVisited, int KeyID)
{
    bool HaveSafe = false;
    VertexQueue VQ = CreateQueue();
    Add2Queue(VQ, V);
    while (!IsEmpty(VQ) && !HaveSafe)
    {
        Vertex TempVertex = DeleteQ(VQ);
        if (!VertexVisited[TempVertex->ID])
        {
            VertexVisited[TempVertex->ID] = true;
        }
        while (TempVertex->Next && !HaveSafe)
        {
            TempVertex = TempVertex->Next;
            if (TempVertex->ID == KeyID)
            {
                HaveSafe = true;
            }
            else
            {
                if (!VertexVisited[TempVertex->ID])
                {
                    Add2Queue(VQ, AdjacencyList[TempVertex->ID]);
                }
            }
        }
    }
    return HaveSafe;
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