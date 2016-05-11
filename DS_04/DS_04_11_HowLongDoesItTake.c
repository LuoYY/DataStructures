/*
* Data Structures in C
* How Long Does It Take
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

Queue CreateQueue();
bool IsEmpty(Queue Q);
void Push2Queue(Queue Q, ElementType elem);
ElementType DeleteQ(Queue Q);

int main(int argc, char const *argv[])
{
    int i, j, N, M;
    int ElementTypeID1, ElementTypeID2, Weight, FinishID = -1;
    Queue Q = CreateQueue();
    scanf("%d %d", &N, &M);
    int **Distances = (int**)malloc(N * sizeof(int*));
    int *Indegree = (int*)malloc(N * sizeof(int));
    int *Outdegree = (int*)malloc(N * sizeof(int));
    int *Date = (int*)malloc(N * sizeof(int));
    for (i = 0; i < N; ++i)
    {
        Indegree[i] = Outdegree[i] = Date[i] = 0;
        Distances[i] = (int*)malloc(N * sizeof(int));
        for (j = 0; j < N; ++j)
        {
            Distances[i][j] = -1;
        }
    }
    for (i = 0; i < M; ++i)
    {
        scanf("%d %d %d", &ElementTypeID1, &ElementTypeID2, &Weight);
        Outdegree[ElementTypeID1] += 1;
        Indegree[ElementTypeID2] += 1;
        Distances[ElementTypeID1][ElementTypeID2] = Weight;
    }
    for (i = 0; i < N; ++i)
    {
        if (Indegree[i] == 0)
        {
            Push2Queue(Q, i);
        }
    }
    for (i = 0; i < N; ++i)
    {
        int id = IsEmpty(Q) ? -1 : DeleteQ(Q);
        if (id == -1)
        {
            break;
        }
        for (j = 0; j < N; ++j)
        {
            if (Distances[i][j] != -1)
            {
                Indegree[j] -= 1;
                if (Date[j] < Date[i] + Distances[i][j])
                {
                    Date[j] = Date[i] + Distances[i][j];
                }
            }
            if (i != j && Indegree[j] == 0)
            {
                Push2Queue(Q, j);
            }
        }
    }
    bool IsFirst = true;
    for (j = 0; j < N; ++j)
    {
        int tmpid = Outdegree[j]
        if (tmpid == 0 && (IsFirst || Date[tmpid] > Date[FinishID]) )
        {
            FinishID = j;
            IsFirst = false;
        }
    }
    if (i == N)
    {
        printf("%d\n", Date[FinishID]);
    }
    else
    {
        printf("Impossible\n");
    }
    return 0;
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