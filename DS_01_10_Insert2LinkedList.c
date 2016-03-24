/*
* Data Structures in C
* Insert a integer to a incremental int linked list
* Without distructing its orderliness
* 20160324
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node *NodePtr;

struct Node
{
	int Data;
	NodePtr Next;
};

NodePtr Insert(NodePtr L, int X);

int main(int argc, char const *argv[])
{
	int S[6] = {1,5,2,8,4,9}, i;
	NodePtr L = NULL;
	for (i = 0; i < 6; ++i)
	{
		L = Insert(L, S[i]);
	}
	while(L)
	{
		printf("%d\n", L->Data);
		L = L->Next;
	}
	return 0;
}

/* Add a blank head NodePtr to make the code clear, clean, help maintain */
NodePtr Insert(NodePtr L, int X)
{
	NodePtr Front, Curr;
	NodePtr Head = (NodePtr)malloc(sizeof(struct Node));

	Head->Next = L;
	Front = Head;
	Curr = Front->Next;

	NodePtr temp = (NodePtr)malloc(sizeof(struct Node));
	temp->Data = X;
	temp->Next = NULL;

	while ( Curr && X > Curr->Data)
	{
		Front = Curr;
		Curr = Front->Next;
	}

	temp->Next = Curr;
	Front->Next = temp;
	L = Head->Next;

	free(Head);

	return L;
}

