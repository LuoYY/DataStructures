/*
* Data Structures in C
* List all connected set of graph by DFS and BFS.
* LuoYingYing
* 20160429
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Vertex *V;
typedef struct LinkQueue *VertexQueue;
struct Vertex
{
	int ID;
	V Next;
};

typedef struct Node
{
	V Data;
	struct Node *Next;
}QNode;

struct LinkQueue
{
	QNode *Rear;
	QNode *Front;
};

void SetEdge(V *AdjacencyList, int VertexID1, int VertexID2);
void Insert2List(V VertexNode, int VertexID);
void DFS(V VertexNode, V *AdjacencyList, bool *VertexVisited);
void BFS(V VertexNode, V *AdjacencyList, bool *VertexVisited);
void Add2Queue(VertexQueue VQ, V VertexNode);
bool IsEmpty(VertexQueue VQ);
V DeleteQ(VertexQueue VQ);
VertexQueue CreateQueue();

int main(int argc, char const *argv[])
{
	int i;
	int NumOfVertex, NumOfEdge;
	scanf("%d %d", &NumOfVertex, &NumOfEdge);
	bool *VertexVisited = (bool*)malloc(NumOfVertex * sizeof(bool));
	V *AdjacencyList = (V*)malloc(NumOfVertex * sizeof(struct Vertex));
	for (i = 0; i < NumOfVertex; ++i)
	{
		AdjacencyList[i] = (V)malloc(sizeof(struct Vertex));
		AdjacencyList[i]->ID = i;
		AdjacencyList[i]->Next = NULL;
		VertexVisited[i] = false;
	}
	for (i = 0; i < NumOfEdge; ++i)
	{
		int VertexID1, VertexID2;
		scanf("%d %d", &VertexID1, &VertexID2);
		SetEdge(AdjacencyList, VertexID1, VertexID2);
	}
	for (i = 0; i < NumOfVertex; ++i)
	{
		if (!VertexVisited[i])
		{
			printf("{ ");
			DFS(AdjacencyList[i], AdjacencyList, VertexVisited);
			printf("}\n");
		}
	}
	for (i = 0; i < NumOfVertex; ++i)
	{
		VertexVisited[i] = false;
	}
	for (i = 0; i < NumOfVertex; ++i)
	{
		if (!VertexVisited[i])
		{
			printf("{ ");
			BFS(AdjacencyList[i], AdjacencyList, VertexVisited);
			printf("}\n");
		}
	}
	return 0;
}

void SetEdge(V *AdjacencyList, int VertexID1, int VertexID2)
{
	Insert2List(AdjacencyList[VertexID1], VertexID2);
	Insert2List(AdjacencyList[VertexID2], VertexID1);
}


void Insert2List(V VertexNode, int VertexID)
{
	if (!VertexNode->Next || VertexNode->Next->ID >= VertexID)
	{
		V TempVertex = (V)malloc(sizeof(struct Vertex));
		TempVertex->ID = VertexID;
		TempVertex->Next = VertexNode->Next ? VertexNode->Next : NULL;
		VertexNode->Next = TempVertex;
	}
	else
	{
		Insert2List(VertexNode->Next, VertexID);
	}
}

void DFS(V VertexNode, V *AdjacencyList, bool *VertexVisited)
{
	if (!VertexVisited[VertexNode->ID])
	{
		printf("%d ", VertexNode->ID);
		VertexVisited[VertexNode->ID] = true;
	}
	while (VertexNode->Next)
	{
		VertexNode = VertexNode->Next;
		if (!VertexVisited[VertexNode->ID])
		{
			DFS(AdjacencyList[VertexNode->ID], AdjacencyList, VertexVisited);
		}
	}
}

void BFS(V VertexNode, V *AdjacencyList, bool *VertexVisited)
{
	VertexQueue VQ = CreateQueue();
	Add2Queue(VQ, VertexNode);
	while (!IsEmpty(VQ))
	{
		V TempVertex = DeleteQ(VQ);
		if (!VertexVisited[TempVertex->ID])
		{
			printf("%d ", TempVertex->ID);
			VertexVisited[TempVertex->ID] = true;
		}
		while (TempVertex->Next)
		{
			TempVertex = TempVertex->Next;
			if (!VertexVisited[TempVertex->ID])
			{
				Add2Queue(VQ, AdjacencyList[TempVertex->ID]);
			}
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

void Add2Queue(VertexQueue VQ, V VertexNode)
{
	QNode *temp = (QNode*)malloc(sizeof(QNode));
	temp->Data = VertexNode;
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

V DeleteQ(VertexQueue VQ)
{
	if (!IsEmpty(VQ))
	{
		QNode *temp = VQ->Front;
		V VertexNode = temp->Data;
		VQ->Front = VQ->Front->Next;
		free(temp);
		return VertexNode;
	}
}