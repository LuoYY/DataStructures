/*
* Data Structures in C
* Given a tree, you are supposed to list all the leaves.
* In the order of top down, and left to right.
* 20160416
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct BinaryTree *BT;
typedef struct LinkQueue *BTQ;

struct BinaryTree
{
    int Data;
    int Left;
    int Right;
};

typedef struct Node
{
    BT Data;
    struct Node *Next;
}QNode;

struct LinkQueue
{
    QNode *Rear;
    QNode *Front;
};


BT* CreatBT(int N, int *root);
BT DeleteQ(BTQ btQ);
BTQ CreatBTQueue();
bool IsEmpty(BTQ btQ);
void Add2Queue(BTQ btQ, BT bt);
void ListLeaves(BT* btArray, int root);


int main(int argc, char const *argv[])
{
    int N, i, root;
    scanf("%d", &N);
    BT* btArray = CreatBT(N, &root);
    ListLeaves(btArray, root);
    return 0;
}

BT* CreatBT(int N, int *root)
{
    int i;
    char left, right, enter;
    bool* isRoot = malloc(N * sizeof(bool));
    BT* btArray = (BT*)malloc(N * sizeof(BT));
    for (i = 0; i < N; ++i)
    {
        isRoot[i] = true;
    }
    scanf("%c", &enter);
    for (i = 0; i < N; ++i)
    {
        btArray[i] = (BT)malloc(sizeof(struct BinaryTree));
        scanf("%c %c%c", &left, &right, &enter);
        btArray[i]->Data = i;
        btArray[i]->Left = left == '-' ? -1 : left - '0';
        btArray[i]->Right = right == '-' ? -1 : right - '0';
        if (btArray[i]->Left != -1)
        {
            isRoot[btArray[i]->Left] = false;
        }
        if (btArray[i]->Right != -1)
        {
            isRoot[btArray[i]->Right] = false;
        }
    }
    for (i = 0; i < N; ++i)
    {
        if(isRoot[i] == true)
        {
            *root = i;
            break;
        }
    }
    return btArray;
}


void ListLeaves(BT* btArray, int root)
{
    BT bt;
    bool isFirst = true;
    BTQ btQ = CreatBTQueue();
    Add2Queue(btQ, btArray[root]);
    while(!IsEmpty(btQ))
    {
        bt = DeleteQ(btQ);
        if(bt->Left == -1 && bt->Right == -1)
        {
            if(!isFirst)
            {
                printf(" ");
            }
            printf("%d", bt->Data);
            isFirst = false;
        }
        else
        {
            if (bt->Left != -1)
            {
                Add2Queue(btQ, btArray[bt->Left]);
            }
            if (bt->Right != -1)
            {
                Add2Queue(btQ, btArray[bt->Right]);
            }
        }
    }
}

BTQ CreatBTQueue()
{
    BTQ btQ = (BTQ)malloc(sizeof(struct LinkQueue));
    btQ->Rear = NULL;
    btQ->Front = NULL;
    return btQ;
}

bool IsEmpty(BTQ btQ)
{
    return btQ->Front == NULL;
}

void Add2Queue(BTQ btQ, BT bt)
{
    QNode *temp = (QNode*)malloc(sizeof(QNode));
    temp->Data = bt;
    temp->Next = NULL;
    if (btQ->Front == NULL)
    {
        btQ->Front = temp;
    }
    else
    {
        btQ->Rear->Next = temp;
    }
    btQ->Rear = temp;
}

BT DeleteQ(BTQ btQ)
{
    if(!IsEmpty(btQ))
    {
        QNode *temp = btQ->Front;
        BT front = temp->Data;
        btQ->Front = btQ->Front->Next;
        free(temp);
        return front;
    }
}