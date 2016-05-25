/*
* Data Structures in C
* Hashing - Hard Version
* LuoYingYing
* 20160520
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//#define scanf scanf_s

typedef struct Node *V;
struct Node
{
	int Data;
	V Next;
};

typedef struct QNode *QNodePtr;
struct QNode
{
	int Data;
	QNodePtr Next;
};

typedef struct QueueNode *Queue;
struct QueueNode
{
	QNodePtr Front;
	QNodePtr Rear;
};

void ReadData(int *H, int *R, int N);
void HandleData(int *H, int *R, int *Indegree, V *AdjL, int N);
void TopSort(Queue Q, V *AdjL, int *H, int *Indegree);
void Insert2AdjL(V *AdjL, int VertexID1, int VertexID2);
void CreateQ(Queue *Q);
void Push2Q(Queue Q, int VertexID, int *H);
int DeleteQ(Queue Q);

int main(int argc, char const *argv[])
{
	int N;
	scanf("%d", &N);
	int *H = malloc(N * sizeof(int));
	int *R = malloc(N * sizeof(int));
	int *Indegree = malloc(N * sizeof(int));
	int *Outdegree = malloc(N * sizeof(int));
	V *AdjL = malloc(N * sizeof(V));
	V *Rear = malloc(N * sizeof(V));
	ReadData(H, R, N);
	HandleData(H, R, Indegree, AdjL, N);
	return 0;
}

void ReadData(int *H, int *R, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		scanf("%d", &H[i]);
		if (H[i] > 0)
		{
			R[i] = H[i] % N;
		}
		else
		{
			R[i] = -1;
		}
	}
}

void HandleData(int *H, int *R, int *Indegree, V *AdjL, int N)
{
	int i, j;
	Queue Q = NULL;
	CreateQ(&Q);
	for (i = 0; i < N; i++)
	{
		AdjL[i] = NULL;
		Indegree[i] = 0;
	}
	for (i = 0; i < N; i++)
	{
		if (R[i] >= 0)
		{
			if (R[i] < i)
			{
				for (j = R[i]; j < i; j++)
				{
					Indegree[i] += 1;
					Insert2AdjL(AdjL, j, i);
				}
			}
			else if (R[i] > i)
			{
				for (j = R[i]; j < i + N; j++)
				{
					Indegree[i] += 1;
					Insert2AdjL(AdjL, j % N, i);
				}
			}
		}
	}

	for (i = 0; i < N; i++)
	{
		if (Indegree[i] == 0 && R[i] >= 0)
		{
			Push2Q(Q, i, H);
		}
	}
	TopSort(Q, AdjL, H, Indegree);
}


void TopSort(Queue Q, V *AdjL, int *H, int *Indegree)
{
	bool IsFirst = true;
	while (Q->Front != NULL)
	{
		int VertexID = DeleteQ(Q);
		if (IsFirst)
		{
			IsFirst = false;
		}
		else
		{
			printf(" ");
		}
		printf("%d", H[VertexID]);
		V Tmp = AdjL[VertexID];
		while (Tmp != NULL)
		{
			Indegree[Tmp->Data]--;
			if (Indegree[Tmp->Data] == 0)
			{
				Push2Q(Q, Tmp->Data, H);
			}
			Tmp = Tmp->Next;
		}
	}
	printf("\n");
}

void Insert2AdjL(V *AdjL, int VertexID1, int VertexID2)
{
	V Tmp = malloc(sizeof(struct Node));
	Tmp->Data = VertexID2;
	Tmp->Next = AdjL[VertexID1];
	AdjL[VertexID1] = Tmp;
}

void CreateQ(Queue *Q)
{
	*Q = malloc(sizeof(struct QueueNode));
	(*Q)->Front = NULL;
	(*Q)->Rear = NULL;
}

void Push2Q(Queue Q, int VertexID, int *H)
{
	QNodePtr Tmp = malloc(sizeof(struct QNode));
	Tmp->Data = VertexID;
	Tmp->Next = NULL;
	if (Q->Front == NULL)
	{
		Q->Front = Q->Rear = Tmp;
	}
	else
	{
		QNodePtr TmpFront = Q->Front;
		if (H[TmpFront->Data] < H[Tmp->Data])
		{
			Tmp->Next = TmpFront;
			Q->Front = Tmp;
		}
		else
		{
			while( TmpFront->Next != NULL && H[TmpFront->Next->Data] < H[Tmp->Data])
			{
				TmpFront = TmpFront->Next;
			}
			Tmp->Next = TmpFront->Next;
			TmpFront->Next = Tmp;
		}
	}
}

int DeleteQ(Queue Q)
{
	int Data = Q->Front->Data;
	QNodePtr Tmp = Q->Front;
	Q->Front = Tmp->Next;
	free(Tmp);
	return Data;
}