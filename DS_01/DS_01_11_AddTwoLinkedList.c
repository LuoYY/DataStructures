/*
* Data Structures in C
* Add two incremental int linked list
* Without mallocing new node
* 20160328
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
NodePtr AddTwoLinkedList(NodePtr L1, NodePtr L2);
void printLinkedList(NodePtr L);

int main(int argc, char const *argv[])
{
    int S1[4] = {1,5,2}, S2[6] = {3,6,7,8,9,4}, i;
    NodePtr L1 = NULL, L2 = NULL;
    for (i = 0; i < 3; ++i)
    {
        L1 = Insert(L1, S1[i]);
    }
    for (i = 0; i < 6; ++i)
    {
        L2 = Insert(L2, S2[i]);
    }
    printLinkedList(L1);
    printLinkedList(L2);
    printLinkedList(AddTwoLinkedList(L1, L2));
    return 0;
}

NodePtr AddTwoLinkedList(NodePtr L1, NodePtr L2)
{
    NodePtr L;
    if (L1 == NULL || L2 == NULL)
    {
        L = L1 == NULL ? L2:L1;
    }
    else
    {
        NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
        NodePtr Curr = Head;
        while(L1 && L2)
        {
            if (L1->Data <= L2->Data)
            {
                Curr->Next = L1;
                L1 = L1->Next;
            }
            else
            {
                Curr->Next = L2;
                L2 = L2->Next;
            }
            Curr = Curr->Next;
            if (Curr->Next == NULL)
            {
                Curr->Next = L1 == NULL ? L2:L1;
            }
        }
        L = Head->Next;
        free(Head);
    }
    return L;
}


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

void printLinkedList(NodePtr L)
{
    while(L)
    {
        printf("%d", L->Data);
        if (L->Next != NULL)
        {
            printf("->");
        }
        L = L->Next;
    }
    printf("\n");
}