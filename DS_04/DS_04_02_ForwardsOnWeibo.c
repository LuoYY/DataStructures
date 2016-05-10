/*
* Data Structures in C
* Forwards on Weibo.
* LuoYingYing
* 20160429
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct VNode *Vertex;
struct VNode
{
	int ID;
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

int CountVertexVisited(bool *VertexVisited, int N);
void Insert2AdjacencyList(Vertex VertexNode, int VertexID);
void ResetVertexVisited(bool *VertexVisited, int N);
void BFS(Vertex V, Vertex *AdjacencyList, bool *VertexVisited, int LimitOfDepth);
bool IsEmpty(VertexQueue VQ);
void Add2Queue(VertexQueue VQ, Vertex V);
Vertex DeleteQ(VertexQueue VQ);
VertexQueue CreateQueue();


int main(int argc, char const *argv[])
{
	int i, j;
	int NumOfVertex, LimitOfLevels;
	scanf("%d %d", &NumOfVertex, &LimitOfLevels);
	bool *VertexVisited = (bool*)malloc(NumOfVertex * sizeof(bool));
	Vertex *AdjacencyList = (Vertex*)malloc(NumOfVertex * sizeof(struct VNode));
	for (i = 0; i < NumOfVertex; ++i)
	{
		AdjacencyList[i] = (Vertex)malloc(sizeof(struct VNode));
		AdjacencyList[i]->ID = i;
		AdjacencyList[i]->Next = NULL;
	}
	for (i = 0; i < NumOfVertex; ++i)
	{
		int NumOfFollowID, FollowID;
		scanf("%d", &NumOfFollowID);
		for (j = 0; j < NumOfFollowID; ++j)
		{
			scanf("%d", &FollowID);
			Insert2AdjacencyList(AdjacencyList[FollowID - 1], i);
		}
	}
	int NumOfQueryID, UserID;
	scanf("%d", &NumOfQueryID);
	for (i = 0; i < NumOfQueryID; ++i)
	{
		ResetVertexVisited(VertexVisited, NumOfVertex);
		scanf("%d", &UserID);
		BFS(AdjacencyList[UserID - 1], AdjacencyList, VertexVisited, LimitOfLevels);
		printf("%d\n", CountVertexVisited(VertexVisited, NumOfVertex) - 1);
	}
	return 0;
}

void Insert2AdjacencyList(Vertex VertexNode, int VertexID)
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
		Insert2AdjacencyList(VertexNode->Next, VertexID);
	}
}



void BFS(Vertex V, Vertex *AdjacencyList, bool *VertexVisited, int LimitOfDepth)
{
	VertexQueue VQ = CreateQueue();
	int Depth = 0;
	int last = V->ID, tail, dqID;
	Add2Queue(VQ, V);
	VertexVisited[V->ID] = true;
	while (!IsEmpty(VQ) && Depth < LimitOfDepth)
	{
		Vertex TempVertex = DeleteQ(VQ);
		dqID = TempVertex->ID;
		while (TempVertex->Next)
		{
			TempVertex = TempVertex->Next;
			if (!VertexVisited[TempVertex->ID])
			{
				VertexVisited[TempVertex->ID] = true;
				Add2Queue(VQ, AdjacencyList[TempVertex->ID]);
				tail = TempVertex->ID;
			}
		}
		if (dqID == last)
		{
			Depth++;
			last = tail;
		}
	}
}

void ResetVertexVisited(bool *VertexVisited, int N)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		VertexVisited[i] = false;
	}
}

int CountVertexVisited(bool *VertexVisited, int N)
{
	int i, cnt = 0;
	for (i = 0; i < N; ++i)
	{
		if (VertexVisited[i] == true)
		{
			cnt++;
		}
	}
	return cnt;
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