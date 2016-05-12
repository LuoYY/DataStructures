/*
* Data Structures in C
* Key Activities
* LuoYingYing
* 20160511
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define scanf scanf_s

typedef int ElementType;
typedef struct LinkQueue *Queue;
typedef struct Node *QNode;

struct Node
{
    ElementType Data;
    QNode Next;
};

struct LinkQueue
{
    QNode Rear;
    QNode Front;
};

typedef struct AdjListNode *AdjList;
struct AdjListNode
{
    ElementType Data;
    ElementType Weight;
    AdjList Next;
};

void Initialization(AdjList *ALS, int *Indegree, int *Earliest, int * Latest, int N, int M);
int CalcEarliest(AdjList *ALS, Queue Q, int *Indegree, int *Earliest, int N);
void CalcLatest(AdjList *ALS, int *Earliest, int *Latest, int *Indegree, int FinishID, int N);
int GetLatest(AdjList *ALS, int *Latest, int id);
void KeyActivities(AdjList *ALS, int *Earliest, int *Latest, int N);
void Push2AdjList(AdjList *AL, ElementType elem, ElementType weight);

Queue CreateQueue();
bool IsEmpty(Queue Q);
void Push2Queue(Queue Q, ElementType elem);
ElementType DeleteQ(Queue Q);

int main(int argc, char const *argv[])
{
    int N, M;
    int FinishID = -1;
    Queue Q = CreateQueue();
    scanf("%d %d", &N, &M);
    int *Indegree = (int*)malloc(N * sizeof(int));
    int *Earliest = (int*)malloc(N * sizeof(int));
    int *Latest = (int*)malloc(N * sizeof(int));
    AdjList *ALS = (AdjList*)malloc(N * sizeof(AdjList));
    Initialization(ALS, Indegree, Earliest, Latest, N, M);
    FinishID = CalcEarliest(ALS, Q, Indegree, Earliest, N);
    if (FinishID == -1)
    {
        printf("0\n");
    }
    else
    {
        printf("%d\n", Earliest[FinishID]);
        CalcLatest(ALS, Earliest, Latest, Indegree, FinishID, N);
        KeyActivities(ALS, Earliest, Latest, N);
    }
    return 0;
}

void Initialization(AdjList *ALS, int *Indegree, int *Earliest, int * Latest, int N, int M)
{
    int i;
    int ElementTypeID1, ElementTypeID2, Weight;
    for (i = 0; i < N; ++i)
    {
        Indegree[i] = Earliest[i] = 0;
        Latest[i] = -1;
        ALS[i] = NULL;
    }
    for (i = 0; i < M; ++i)
    {
        scanf("%d %d %d", &ElementTypeID1, &ElementTypeID2, &Weight);
        Push2AdjList(&ALS[ElementTypeID1 - 1], ElementTypeID2 - 1, Weight);
        Indegree[ElementTypeID2 - 1] += 1;
    }
}

int CalcEarliest(AdjList *ALS, Queue Q, int *Indegree, int *Earliest, int N)
{
    int i, j, id, FinishID = -1;
    bool IsFirst = true;
    for (i = 0; i < N; ++i)
    {
        if (Indegree[i] == 0)
        {
            Push2Queue(Q, i);
        }
    }
    for (i = 0; i < N; ++i)
    {
        id = IsEmpty(Q) ? -1 : DeleteQ(Q);
        if (id == -1)
        {
            break;
        }
        AdjList Tmp = ALS[id];
        while (Tmp)
        {
            j = Tmp->Data;
            Indegree[j] -= 1;
            if (Earliest[j] < Earliest[id] + Tmp->Weight)
            {
                Earliest[j] = Earliest[id] + Tmp->Weight;
            }
            if (Indegree[j] == 0)
            {
                Push2Queue(Q, j);
            }
            Tmp = Tmp->Next;
        }
    }
    if (i == N)
    {
        for (j = 0; j < N; ++j)
        {
            if (ALS[j] == NULL && (IsFirst || Earliest[j] > Earliest[FinishID]))
            {
                FinishID = j;
                IsFirst = false;
            }
        }
    }
    return FinishID;
}

void CalcLatest(AdjList *ALS, int *Earliest, int *Latest, int *Indegree, int FinishID, int N)
{
    int i, j, id;
    for (i = 0; i < N; ++i)
    {
        if (ALS[i] == NULL)
        {
            Latest[i] = Earliest[FinishID];
        }
    }
    for (i = 0; i < N; ++i)
    {
        if (Indegree[i] == 0)
        {
            GetLatest(ALS, Latest, i);
        }
    }
}

int GetLatest(AdjList *ALS, int *Latest, int id)
{
    bool IsFirst = true;
    int MinLatest = Latest[id], TmpLatest;
    if (MinLatest == -1)
    {
        AdjList AL = ALS[id];
        while (AL)
        {
            TmpLatest = GetLatest(ALS, Latest, AL->Data) - AL->Weight;
            if (IsFirst || TmpLatest < MinLatest)
            {
                MinLatest = TmpLatest;
                IsFirst = false;
            }
            AL = AL->Next;
        }
    }
    Latest[id] = MinLatest;
    return MinLatest;
}

void KeyActivities(AdjList *ALS, int *Earliest, int *Latest, int N)
{
    int i, j;
    AdjList Tmp;
    for (i = 0; i < N; ++i)
    {
        Tmp = ALS[i];
        while (Tmp)
        {
            if (Latest[Tmp->Data] - Earliest[i] == Tmp->Weight)
            {
                printf("%d->%d\n", i + 1, Tmp->Data + 1);
            }
            Tmp = Tmp->Next;
        }
    }
}

void Push2AdjList(AdjList *AL, ElementType elem, ElementType weight)
{
    AdjList Tmp = (AdjList)malloc(sizeof(struct AdjListNode));
    Tmp->Data = elem;
    Tmp->Weight = weight;
    Tmp->Next = *AL;
    *AL = Tmp;
}

Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct LinkQueue));
    Q->Rear = NULL;
    Q->Front = NULL;
    return Q;
}

bool IsEmpty(Queue Q)
{
    return Q->Front == NULL;
}

void Push2Queue(Queue Q, ElementType elem)
{
    QNode temp = (QNode)malloc(sizeof(QNode));
    temp->Data = elem;
    temp->Next = NULL;
    if (Q->Front == NULL)
    {
        Q->Front = temp;
    }
    else
    {
        Q->Rear->Next = temp;
    }
    Q->Rear = temp;
}

ElementType DeleteQ(Queue Q)
{
    if (!IsEmpty(Q))
    {
        QNode temp = Q->Front;
        ElementType elem = temp->Data;
        Q->Front = Q->Front->Next;
        //free(temp);
        return elem;
    }
}