/*
* Data Structures in C
* Pop Sequence
* Given a stack which can keep M numbers at most.
* Push N numbers in the order of 1, 2, 3, ..., N and pop randomly.
* You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack.
* For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.
* 20160412
* LuoYingYing
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int ElementType;
typedef int Position;
typedef struct SNode *Stack;

struct SNode
{
    int MaxSize;
    Position Top;
    ElementType *Data;
};

Stack CreateStack(int MaxSize);
bool Push(Stack stk, ElementType X);
bool Pop(Stack stk);
bool IsEmpty(Stack stk);
bool IsFull(Stack stk);

int main(int argc, char const *argv[])
{
    int i, j, flag, temp;
    int M, N, K;
    int outputStack; /* 模拟输出[1, 2, 3, ..., N] */
    scanf("%d %d %d", &M, &N, &K);
    for (i = 0; i < K; ++i)
    {
        outputStack = 1;
        flag = true; /* 标记是否已判为错误 */
        Stack stk = CreateStack(M);
        for (j = 0; j < N; ++j)
        {
            scanf("%d", &temp);
            while (flag)
            {
                if (IsEmpty(stk) || (!IsFull(stk) && stk->Data[stk->Top] != temp))
                {
                    Push(stk, outputStack++);
                }
                else if (stk->Data[stk->Top] == temp)
                {
                    Pop(stk);
                    break;
                }
                else
                {
                    flag = false;
                }
            }
        }
        printf("%s\n", flag ? "YES" : "NO");
    }
    return 0;
}

Stack CreateStack(int MaxSize)
{
    Stack stk = (Stack)malloc(sizeof(struct SNode));
    stk->MaxSize = MaxSize;
    stk->Top = -1;
    stk->Data = (ElementType*)malloc(MaxSize * sizeof(ElementType));
    return stk;
}

bool Push(Stack stk, ElementType X)
{
    if (IsFull(stk))
    {
        printf("The stack is Full.\n");
        return false;
    }
    else
    {
        stk->Data[++(stk->Top)] = X;
        return true;
    }
}

bool Pop(Stack stk)
{
    if (IsEmpty(stk))
    {
        printf("The stack is empty.\n");
        return false;
    }
    else
    {
        (stk->Top)--;
        return true;
    }
}

bool IsEmpty(Stack stk)
{
    return stk->Top == -1 ? true : false;
}

bool IsFull(Stack stk)
{
    return stk->Top == stk->MaxSize - 1 ? true : false;
}