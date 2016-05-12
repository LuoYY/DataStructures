/*
* Data Structures in C
* Saving James Bond - Hard Version.
* LuoYingYing
* 20160507
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define scanf scanf_s

typedef struct VNode *Vertex;
struct VNode
{
    int ID;
    double Weight;
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

typedef struct PointNode *Point;
struct PointNode
{
    int X;
    int Y;
};

typedef struct StackNode *Stack;
struct StackNode
{
    int Data;
    Stack Next;
};


VertexQueue CreateQueue();
bool IsEmpty(VertexQueue VQ);
void Add2Queue(VertexQueue VQ, Vertex V);
Vertex DeleteQ(VertexQueue VQ);

void Add2Stack(Stack *stk, int Data);
void PrintStack(Stack stk, Point *Points);

void printS(double *S, int N);

Vertex* CreateGraph(int NumOfVertexes);
void ReadEdge2Graph(Vertex* AdjacencyList, Point *Points, int NumOfVertexes, int LimitOfDistance);
void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, double Weight);
void Insert2AdjacencyList(Vertex VertexNode, int VertexID, double Weight);
void JudgeGraph(Vertex* AdjacencyList, Point *Points, int NumOfVertexes);
bool IsInLake(Point P);
bool CanJumpOfTwoVertexes(Point P1, Point P2, int D);
bool CanFirstJump(Point P, int D);
bool CanJump2Land(Point P, int D);
double CalcDistanceOfFirstJump(Point P);
double CalcDistanceOfJump2Land(Point P);
double CalcDistanceOfTwoVertexes(Point P1, Point P2);

int Back2FirstJumpID(int *Path, int ID);

void BFS(Vertex V, Vertex *AdjacencyList, double *WeightOfVertexes, int *Path, int N);

void ResetWeightOfVertexes(double *WeightOfVertexes, int N);
Stack CountWeightOfVertexes(double *WeightOfVertexes, int *Path, int N);


int main(int argc, char const *argv[])
{
    int NumOfCrocodiles, NumOfVertexes, LimitOfJump;
    scanf("%d %d", &NumOfCrocodiles, &LimitOfJump);
    NumOfVertexes = NumOfCrocodiles + 2;
    Point *Points = (Point*)malloc(NumOfVertexes * sizeof(Point));
    Vertex *AdjacencyList = CreateGraph(NumOfVertexes);
    ReadEdge2Graph(AdjacencyList, Points, NumOfVertexes, LimitOfJump);
    JudgeGraph(AdjacencyList, Points, NumOfVertexes);
    return 0;
}

bool IsInLake(Point P)
{
    return (P->X <= 50 && P->X >= -50 && P->Y <= 50 && P->Y >= -50) && ((P->X)*(P->X) + (P->Y)*(P->Y) > (15 / 2.0) * (15 / 2.0));
}

void JudgeGraph(Vertex* AdjacencyList, Point *Points, int NumOfVertexes)
{
    double *WeightOfVertexes = (double*)malloc(NumOfVertexes * sizeof(double));
    int *Path = (int*)malloc(NumOfVertexes * sizeof(int));
    ResetWeightOfVertexes(WeightOfVertexes, NumOfVertexes);
    BFS(AdjacencyList[0], AdjacencyList, WeightOfVertexes, Path, NumOfVertexes);
    Stack stk = CountWeightOfVertexes(WeightOfVertexes, Path, NumOfVertexes);
    PrintStack(stk, Points);
}

Vertex* CreateGraph(int NumOfVertexes)
{
    Vertex *AdjacencyList = (Vertex*)malloc(NumOfVertexes * sizeof(Vertex));
    AdjacencyList[0] = (Vertex)malloc(sizeof(struct VNode));
    AdjacencyList[NumOfVertexes - 1] = (Vertex)malloc(sizeof(struct VNode));
    AdjacencyList[0]->ID = 0;
    AdjacencyList[NumOfVertexes - 1]->ID = NumOfVertexes - 1;
    AdjacencyList[0]->Next = AdjacencyList[NumOfVertexes - 1]->Next = NULL;
    return AdjacencyList;
}

void ReadEdge2Graph(Vertex* AdjacencyList, Point *Points, int NumOfVertexes, int LimitOfDistance)
{
    int i, j;
    if ( 50-15/2.0 <= LimitOfDistance)
    {
        SetEdge(AdjacencyList, 0, NumOfVertexes - 1, 50 - 15 / 2.0);
    }
    else
    {
        for (i = 1; i <= NumOfVertexes - 2; ++i)
        {
            Points[i] = (Point)malloc(NumOfVertexes * sizeof(struct PointNode));
            scanf("%d %d", &(Points[i]->X), &(Points[i]->Y));
            AdjacencyList[i] = (Vertex)malloc(sizeof(struct VNode));
            AdjacencyList[i]->ID = i;
            AdjacencyList[i]->Next = NULL;
            if (IsInLake(Points[i]))
            {
                if (CanFirstJump(Points[i], LimitOfDistance))
                {
                    Insert2AdjacencyList(AdjacencyList[0], i, CalcDistanceOfFirstJump(Points[i]));
                }
                if (CanJump2Land(Points[i], LimitOfDistance))
                {
                    Insert2AdjacencyList(AdjacencyList[i], NumOfVertexes - 1, CalcDistanceOfJump2Land(Points[i]));
                }
            }
        }

        for (i = 1; i <= NumOfVertexes - 2; ++i)
        {
            for (j = i; j <= NumOfVertexes - 2; ++j)
            {
                if (i != j && CanJumpOfTwoVertexes(Points[i], Points[j], LimitOfDistance))
                {
                    SetEdge(AdjacencyList, i, j, CalcDistanceOfTwoVertexes(Points[i], Points[j]));
                }
            }
        }
    }
}

void SetEdge(Vertex *AdjacencyList, int VertexID1, int VertexID2, double Weight)
{
    Insert2AdjacencyList(AdjacencyList[VertexID1], VertexID2, Weight);
    Insert2AdjacencyList(AdjacencyList[VertexID2], VertexID1, Weight);
}

void Insert2AdjacencyList(Vertex VertexNode, int VertexID, double Weight)
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

bool CanFirstJump(Point P, int D)
{
    return (P->X)*(P->X) + (P->Y)*(P->Y) <= (15 / 2.0 + D) * (15 / 2.0 + D);
}

bool CanJump2Land(Point P, int D)
{
    return P->X <= -50 + D || P->X >= 50 - D || P->Y <= -50 + D || P->Y >= 50 - D;
}

bool CanJumpOfTwoVertexes(Point P1, Point P2, int D)
{
    return IsInLake(P1) && IsInLake(P2) && (P1->X - P2->X)*(P1->X - P2->X) + (P1->Y - P2->Y)*(P1->Y - P2->Y) <= D * D;
}

double CalcDistanceOfFirstJump(Point P)
{
    return sqrt((P->X)*(P->X) + (P->Y)*(P->Y)) - 15/2.0;
}

double CalcDistanceOfJump2Land(Point P)
{
    double dX = P->X > 0 ? 50 - P->X : 50 + P->X;
    double dY = P->Y > 0 ? 50 - P->Y : 50 + P->Y;
    return dX > dY ? dY : dX;
}

double CalcDistanceOfTwoVertexes(Point P1, Point P2)
{
    return sqrt((P1->X - P2->X)*(P1->X - P2->X) + (P1->Y - P2->Y)*(P1->Y - P2->Y));
}

void BFS(Vertex V, Vertex *AdjacencyList, double *WeightOfVertexes, int *Path, int N)
{
    VertexQueue VQ = CreateQueue();
    WeightOfVertexes[V->ID] = 0;
    Path[V->ID] = -1;
    Add2Queue(VQ, V);
    while (!IsEmpty(VQ))
    {
        printS(WeightOfVertexes, N);
        Vertex TempVertex = DeleteQ(VQ);
        double FatherWeight = WeightOfVertexes[TempVertex->ID];
        int FatherID = TempVertex->ID;
        while (TempVertex->Next)
        {
            TempVertex = TempVertex->Next;
            int ID = TempVertex->ID;
            double Weight = TempVertex->Weight;
            if (WeightOfVertexes[ID] == -1 ||
                (WeightOfVertexes[ID] > FatherWeight + Weight) ||
                (WeightOfVertexes[ID] == FatherWeight + Weight &&
                (WeightOfVertexes[Back2FirstJumpID(Path, Path[ID])] >
                 WeightOfVertexes[Back2FirstJumpID(Path, FatherID)]) ) )
            {
                WeightOfVertexes[ID] = FatherWeight + Weight;
                Path[ID] = FatherID;
                printf("Path id: %d father: %d\n", ID, FatherID);
                printS(WeightOfVertexes, N);
                Add2Queue(VQ, AdjacencyList[ID]);
            }
        }
    }
}

int Back2FirstJumpID(int *Path, int ID)
{
    int index = ID;
    while (Path[Path[index]] != -1)
    {
        index = Path[index];
    }
    return index;
}

void printS(double *S, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        printf(" %.2f", S[i]);
    }
    printf("\n");
}

void ResetWeightOfVertexes(double *WeightOfVertexes, int N)
{
    int i;
    for (i = 0; i < N; ++i)
    {
        WeightOfVertexes[i] = -1;
    }
}

Stack CountWeightOfVertexes(double *WeightOfVertexes, int *Path, int N)
{
    Stack stk = NULL;
    if (WeightOfVertexes[N - 1] != -1)
    {
        int index = N - 1;
        while (Path[index] != -1)
        {
            Add2Stack(&stk, index);
            index = Path[index];
        }
    }
    return stk;
}

void Add2Stack(Stack *stk, int Data)
{
    Stack tmp = (Stack)malloc(sizeof(struct StackNode));
    tmp->Data = Data;
    tmp->Next = *stk;
    *stk = tmp;
}

void PrintStack(Stack stk, Point *Points)
{
    if (stk == NULL)
    {
        printf("0\n");
    }
    else
    {
        Stack tmp = stk;
        int cnt = 0;
        while (tmp != NULL)
        {
            cnt++;
            tmp = tmp->Next;
        }
        printf("%d\n", cnt);
        while (stk->Next != NULL)
        {
            printf("%d %d\n", Points[stk->Data]->X, Points[stk->Data]->Y);
            stk = stk->Next;
        }
    }
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