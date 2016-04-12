/*
* Data Structures in C
* Calc the sum and product of two polynomials in one variable
* 20160331
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>


typedef struct Node *NodePtr;

struct Node
{
    int Coef;
    int Expon;
    NodePtr Next;
};

NodePtr ReadPolyn();
NodePtr Insert2Polyn(NodePtr L, int Coef, int Expon);
NodePtr AddPolyn(NodePtr L1, NodePtr L2);
NodePtr MultiplyPolyn(NodePtr L1, NodePtr L2);
void PrintPolyn(NodePtr L);

int main(int argc, char const *argv[])
{
    NodePtr L1 = NULL, L2 = NULL;
    L1 = ReadPolyn();
    L2 = ReadPolyn();
    PrintPolyn(MultiplyPolyn(L1, L2));
    PrintPolyn(AddPolyn(L1, L2));
    return 0;
}

NodePtr ReadPolyn()
{
    NodePtr L = NULL;
    int i, N, Coef, Expon;
    scanf("%d",&N);
    for (i = 0; i < N; ++i)
    {
        scanf("%d %d", &Coef, &Expon);
        L = Insert2Polyn(L, Coef, Expon);
    }
    return L;
}

NodePtr Insert2Polyn(NodePtr L, int Coef, int Expon)
{
    NodePtr Head = (NodePtr)malloc(sizeof(struct Node));
    NodePtr Front = Head;
    Head->Next = L;

    NodePtr Temp = (NodePtr)malloc(sizeof(struct Node));
    Temp->Coef = Coef;
    Temp->Expon = Coef == 0 ? 0 : Expon;
    Temp->Next = NULL;

    if( L == NULL)
    {
        Front->Next = Temp;
    }
    else if ( Coef == 0 )
    {
        free(Temp);
    }
    else if ( L->Coef == 0 )
    {
        Front->Next = Temp;
        free(L);
    }
    else
    {
        while( L && L->Expon > Expon)
        {
            L = L->Next;
            Front = Front->Next;
        }
        if( L != NULL && L->Expon == Expon )
        {
            L->Coef += Coef;
            if (L->Coef == 0)
            {
                L->Expon = 0;
                if ( L->Next != NULL || Front != Head)
                {
                    Front->Next = L->Next;
                    free(L);
                }
            }
            free(Temp);
        }
        else
        {
            Temp->Next = Front->Next;
            Front->Next = Temp;
        }
    }


    L = Head->Next;
    free(Head);

    return L;
}

NodePtr AddPolyn(NodePtr L1, NodePtr L2)
{
    NodePtr L = NULL;
    while( L1 || L2 )
    {
        if (L1)
        {
            L = Insert2Polyn(L, L1->Coef, L1->Expon);
            L1 = L1->Next;
        }
        if (L2)
        {
            L = Insert2Polyn(L, L2->Coef, L2->Expon);
            L2 = L2->Next;
        }
    }
    return L;
}

NodePtr MultiplyPolyn(NodePtr L1, NodePtr L2)
{
    NodePtr L = NULL;
    if (L1 && L2)
    {
        while(L1)
        {
            NodePtr Temp = L2;
            while(Temp)
            {
                L = Insert2Polyn(L, L1->Coef * Temp->Coef, L1->Expon + Temp->Expon);
                Temp = Temp->Next;
            }
            L1 = L1->Next;
        }
    }
    else
    {
        L = Insert2Polyn(L, 0, 0);
    }
    return L;
}

void PrintPolyn(NodePtr L)
{
    while(L)
    {
        printf("%d %d", L->Coef,L->Expon);
        if (L->Next != NULL)
        {
            printf(" ");
        }
        L = L->Next;
    }
    printf("\n");
}