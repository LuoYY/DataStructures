/*
* Data Structures in C
* Given a constant K and a singly linked list L
* you are supposed to reverse the links of every K elements on L
* For example, given L being 1→2→3→4→5→6
* if K = 3, then you must output 3→2→1→6→5→4
* if K = 4, you must output 4→3→2→1→5→6
* There are two impl
* 20160330
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node *NodePtr;
struct Node
{
    int Address;
    int Data;
    int Next;
    NodePtr Link;
};

void ReadLinkedList(int N, NodePtr S[]);
void PrintLinkedList(NodePtr L);
NodePtr CreateLinkedList(int Address, NodePtr S[]);
NodePtr ReverseLinkedList1(NodePtr L, int K);
NodePtr ReverseLinkedList2(NodePtr L, int K);
NodePtr Reverse(NodePtr L, int K);

int main(int argc, char const *argv[])
{
    int Address, N, K;
    NodePtr S[100000], L, ReversedL;
    scanf("%d %d %d", &Address, &N, &K);
    ReadLinkedList(N, S);
    L = CreateLinkedList(Address, S);
    ReversedL = ReverseLinkedList1(L, K);
    /* ReversedL = ReverseLinkedList2(L, K); */
    PrintLinkedList(ReversedL);
    return 0;
}

void ReadLinkedList(int N, NodePtr S[])
{
    int i, Address, Data, Next;
    NodePtr L = NULL;
    for (i = 0; i < N; ++i)
    {
        scanf("%d %d %d", &Address, &Data, &Next);
        NodePtr Temp = (NodePtr)malloc(sizeof(struct Node));
        Temp->Address = Address;
        Temp->Data = Data;
        Temp->Next = Next;
        Temp->Link = NULL;
        S[Address] = Temp;
    }
}

void PrintLinkedList(NodePtr L)
{
    while(L)
    {
        printf("%05d %d ", L->Address, L->Data);
        if ( L->Link )
        {
            printf("%05d", L->Link->Address);
        }
        else
        {
            printf("-1");
        }
        printf("\n");
        L = L->Link;
    }
}

NodePtr CreateLinkedList(int Address, NodePtr S[])
{
    NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
    NodePtr L = Head;
    while( Address != -1 )
    {
        NodePtr Temp = S[Address];
        Address = Temp->Next;
        L->Link = Temp;
        L = L->Link;
    }
    L = Head->Link;
    free(Head);
    return L;
}

NodePtr ReverseLinkedList1(NodePtr L, int K)
{
    NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
    NodePtr New, Old, Temp1, Temp2, Curr = Head, ReversedL;
    Curr->Link = L;
    int i, j, cnt = 0;
    while(L)
    {
        L = L->Link;
        cnt++;
    }
    for (i = 0; i < cnt/K; ++i)
    {
        New = Curr->Link;
        Old = New->Link;
        for (j = 0; j < K-1; ++j)
        {
            Temp1 = Old->Link;
            Old->Link = New;
            New = Old;
            Old = Temp1;
        }
        Temp2 = Curr->Link;
        Curr->Link = New;
        Curr = Temp2;
        Curr->Link = Old;
    }
    ReversedL = Head->Link;
    free(Head);
    return ReversedL;
}

NodePtr ReverseLinkedList2(NodePtr L, int K)
{
    NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
    NodePtr Temp = Head, ReversedL;
    Head->Link = L;
    int i, cnt = 0;
    while(L)
    {
        L = L->Link;
        cnt++;
    }
    for (i = 0; i < cnt/K; ++i)
    {
        Temp = Reverse(Temp, K);
    }
    ReversedL = Head->Link;
    free(Head);
    return ReversedL;
}

NodePtr Reverse(NodePtr L, int K)
{
    int i;
    NodePtr New, Old, Temp, Curr;
    Curr = L->Link;
    New = L->Link;
    Old = New->Link;
    for ( i = 0; i < K-1; ++i)
    {
        Temp = Old->Link;
        Old->Link = New;
        New = Old;
        Old = Temp;
    }
    L->Link = New;
    Curr->Link = Old;
    return Curr;
}