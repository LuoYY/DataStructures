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
    NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
    NodePtr Front = Head;
    Head->Next = L;

    NodePtr Temp = (NodePtr)malloc(sizeof(struct Node));
    Temp->Data = X;
    Temp->Next = NULL;

    while ( L && X > L->Data)
    {
        L = L->Next;
        Front = Front->Next;
    }

    Temp->Next = L;
    Front->Next = temp;

    L = Head->Next;
    free(Head);

    return L;
}

