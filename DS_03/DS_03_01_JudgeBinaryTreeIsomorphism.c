/*
* Data Structures in C
* Judge Binary Tree Isomorphism
* 20160414
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct BinaryTree *BT;
struct BinaryTree
{
    char *Data;
    char *Left;
    char *Right;
};

BT createBT(int N);
bool compareBT(BT A, BT B, int N);

int main(int argc, char const *argv[])
{
    int N1, N2;
    scanf("%d", &N1);
    BT bt1 = createBT(N1);
    scanf("%d", &N2);
    BT bt2 = createBT(N2);
    if ( N1 == N2 && compareBT(bt1, bt2, N1))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}

BT createBT(int N)
{
    int i;
    char enter; /*To eliminate line feed effects*/
    BT bt = (BT)malloc(sizeof(struct BinaryTree));
    bt->Data = (char*)malloc(N * sizeof(char));
    bt->Left = (char*)malloc(N * sizeof(char));
    bt->Right = (char*)malloc(N * sizeof(char));
    scanf("%c", &enter);
    for (i = 0; i < N; ++i)
    {
        scanf("%c %c %c%c", &bt->Data[i], &bt->Left[i], &bt->Right[i], &enter);
    }
    return bt;
}

bool compareBT(BT A, BT B, int N)
{
    int i, j;
    bool cp1 = true, cp2 = true, hasSameElem = true;
    for (i = 0; i < N && (cp1 || cp2) && hasSameElem; ++i)
    {
        hasSameElem = false;
        for (j = 0; j < N; ++j)
        {
            if (A->Data[i] == B->Data[j])
            {
                A->Left[i] = A->Left[i] == '-' ? '-' : A->Data[A->Left[i] - '0'];
                A->Right[i] = A->Right[i] == '-' ? '-' : A->Data[A->Right[i] - '0'];
                B->Left[j] = B->Left[j] == '-' ? '-' : B->Data[B->Left[j] - '0'];
                B->Right[j] = B->Right[j] == '-' ? '-' : B->Data[B->Right[j] - '0'];
                cp1 = A->Left[i] == B->Left[j] && A->Right[i] == B->Right[j];
                cp2 = A->Left[i] == B->Right[j] && A->Right[i] == B->Left[j];
                hasSameElem = true;
                break;
            }
        }
    }
    return (cp1 || cp2) && hasSameElem ;
}