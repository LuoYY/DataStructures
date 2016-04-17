/*
* Data Structures in C
* Judge Two Binary Search Tree is Equal
* 20160417
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct Node *BST;
struct Node
{
    ElementType Data;
    BST Left;
    BST Right;
};

BST creatBST(int N);
void insert2BST(BST* bst, ElementType data);
bool compareBST(BST a, BST b);

int main(int argc, char const *argv[])
{
    int N, L, i;
    while(true)
    {
        scanf("%d", &N);
        if (N > 0)
        {
            scanf("%d", &L);
            BST original = creatBST(N);
            for (i = 0; i < L; ++i)
            {
                BST temp = creatBST(N);
                bool isEqual = compareBST(original, temp);
                printf("%s\n", isEqual ? "Yes":"No");
            }
        }
        else
        {
            break; 
        }
    }
    return 0;
}

BST creatBST(int N)
{
    int i;
    ElementType data;
    BST bst = NULL;
    for (i = 0; i < N; ++i)
    {
        scanf("%d", &data);
        insert2BST(&bst, data);
    }
    return bst;
}

void insert2BST(BST* bst, ElementType data)
{
    if (*bst == NULL)
    {
        BST temp = (BST)malloc(sizeof(struct Node));
        temp->Data = data;
        temp->Left = temp->Right = NULL;
        *bst = temp;
    }
    else
    {
        if (data > (*bst)->Data)
        {
            insert2BST(&(*bst)->Right, data);
        }
        else
        {
            insert2BST(&(*bst)->Left, data);
        }
    }
}

bool compareBST(BST a, BST b)
{
    if ( (a || b) && !(a && b))
    {
        return false;
    }
    else if (!a && !b)
    {
        return true;
    }
    else
    {
        if (a->Data == b->Data && compareBST(a->Left, b->Left) && compareBST(a->Right, b->Right))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}