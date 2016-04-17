/*
* Data Structures in C
* Given a sequence of insertions
* you are supposed to tell the root of the resulting AVL tree
* 20160417
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct AVLTreeNode *AVLTree;
struct AVLTreeNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

void Insert2AVLTree(AVLTree* T, ElementType data);
void LeftLeftRotation(AVLTree* A);
void LeftRightRotation(AVLTree* A);
void RightRightRotation(AVLTree* A);
void RightLeftRotation(AVLTree* A);
void UpdateHeight(AVLTree T);
bool IsBalance(AVLTree T);

int main(int argc, char const *argv[])
{
    int N, i, data;
    AVLTree root = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; ++i)
    {
        scanf("%d", &data);
        Insert2AVLTree(&root, data);
    }
    printf("%d\n", root->Data);
    return 0;
}

void Insert2AVLTree(AVLTree* T, ElementType data)
{
    if (*T == NULL)
    {
        AVLTree temp = (AVLTree)malloc(sizeof(struct AVLTreeNode));
        temp->Data = data;
        temp->Height = 0;
        temp->Left = temp->Right = NULL;
        *T = temp;
    }
    else
    {
        if (data < (*T)->Data)
        {
            Insert2AVLTree(&(*T)->Left, data);
            UpdateHeight(*T);
            if (IsBalance(*T))
            {
                if (data < (*T)->Left->Data)
                {
                    LeftLeftRotation(&(*T));
                }
                else
                {
                    LeftRightRotation(&(*T));
                }
            }
        }
        else
        {
            Insert2AVLTree(&(*T)->Right, data);
            UpdateHeight(*T);
            if (IsBalance(*T))
            {
                if (data > (*T)->Right->Data)
                {
                    RightRightRotation(&(*T));
                }
                else
                {
                    RightLeftRotation(&(*T));
                }
            }
        }
    }
}


void LeftLeftRotation(AVLTree* A)
{
    AVLTree B = (*A)->Left;
    (*A)->Left = B->Right;
    UpdateHeight(*A);
    B->Right = *A;
    UpdateHeight(B);
    *A = B;
}

void LeftRightRotation(AVLTree* A)
{
    RightRightRotation(&(*A)->Left);
    LeftLeftRotation(&(*A));
    /*
    AVLTree B = (*A)->Left;
    AVLTree C = B->Right;
    (*A)->Left = C->Right;
    UpdateHeight(*A);
    B->Right = C->Left;
    UpdateHeight(B);
    C->Left = B;
    C->Right = *A;
    UpdateHeight(C);
    *A = C;
    */
}

void RightRightRotation(AVLTree* A)
{
    AVLTree B = (*A)->Right;
    (*A)->Right = B->Left;
    UpdateHeight(*A);
    B->Left = *A;
    UpdateHeight(B);
    *A = B;
}

void RightLeftRotation(AVLTree* A)
{
    LeftLeftRotation(&(*A)->Right);
    RightRightRotation(&(*A));
    /*
    AVLTree B = (*A)->Right;
    AVLTree C = B->Left;
    (*A)->Right = C->Left;
    UpdateHeight(*A);
    B->Left = C->Right;
    UpdateHeight(B);
    C->Left = *A;
    C->Right = B;
    UpdateHeight(C);
    *A = C;
    */
}

void UpdateHeight(AVLTree T)
{
    int leftHeight, rightHeight;
    leftHeight = T->Left != NULL ? T->Left->Height : -1;
    rightHeight = T->Right != NULL ? T->Right->Height : -1;
    T->Height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

bool IsBalance(AVLTree T)
{
    int leftHeight, rightHeight;
    leftHeight = T->Left != NULL ? T->Left->Height : -1;
    rightHeight = T->Right != NULL ? T->Right->Height : -1;
    return leftHeight - rightHeight == 2 || rightHeight - leftHeight == 2;
}