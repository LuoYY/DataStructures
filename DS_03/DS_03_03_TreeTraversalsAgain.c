/*
* Data Structures in C
* Tree Traversals
* 20160416
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int Operation;
typedef struct Node *NodePtr;
typedef struct Stack *StkPtr;
struct Node
{
    int Data;
    NodePtr Left;
    NodePtr Right;
};

struct Stack
{
    NodePtr Data;
    StkPtr Next;
};

NodePtr Pop(StkPtr stk);
void Push(StkPtr stk, NodePtr data);
void TreeTraversals(NodePtr root, bool* isFirstPrint);

int main(int argc, char const *argv[])
{
    int N, i;
    bool isFirstPush = true, isFirstPrint = true;
    Operation op, previousOp, push = 1, pop = 0;
    NodePtr root, previousPush, previousPop;
    StkPtr stk = (StkPtr)malloc(sizeof(struct Stack));
    stk->Next = NULL;

    scanf("%d", &N);
    for (i = 0; i < 2*N; ++i)
    {
        int cnt = 0;
        char str[8];
        gets(str);
        while(str[cnt] != '\0')
        {
            cnt++;
        }
        if (cnt > 3)
        {
            op = push;
            int data = cnt > 6 ? (str[5]-'0')*10+(str[6]-'0'):(str[5]-'0');
            NodePtr temp = (NodePtr)malloc(sizeof(struct Node));
            temp->Data = data;
            temp->Left = temp->Right = NULL;
            if (isFirstPush)
            {
                root = temp;
                isFirstPush = false;
            }
            else
            {
                if (previousOp == push)
                {
                    previousPush->Left = temp;
                }
                else
                {
                    previousPop->Right = temp;
                }
            }
            Push(stk, temp);
            previousPush = temp;
        }
        else
        {
            op = pop;
            previousPop = Pop(stk);
        }
        previousOp = op;
    }
    
    TreeTraversals(root, &isFirstPrint);
    return 0;
}

void Push(StkPtr stk, NodePtr data)
{
    StkPtr temp = (StkPtr)malloc(sizeof(struct Stack));
    temp->Data = data;
    temp->Next = stk->Next;
    stk->Next = temp;
}

NodePtr Pop(StkPtr stk)
{
    NodePtr nodePtr = NULL;
    if (stk->Next != NULL)
    {
        StkPtr temp = stk->Next;
        nodePtr = temp->Data;
        stk->Next = stk->Next->Next;
        free(temp);
    }
    return nodePtr;
}

void TreeTraversals(NodePtr root, bool* isFirstPrint)
{
    if (root != NULL)
    {
        TreeTraversals(root->Left, isFirstPrint);
        TreeTraversals(root->Right, isFirstPrint);
        if(*isFirstPrint)
        {
            *isFirstPrint = false;
        }
        else
        {
            printf(" ");
        }
        printf("%d", root->Data);
    }
}