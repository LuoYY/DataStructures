/*
* Data Structures in C
* File transfer.
* LuoYingYing
* 20160421
*/

#include <stdlib.h>
#include <stdio.h>

int FindRoot(int *S, int a);
void Check(int *S, int a, int b);
void Union(int *S, int a, int b);
void CheckAll(int *S, int N);

int main(int argc, char const *argv[])
{
    int N, i;
    int a, b;
    int *S;
    char op, ENTER;
    scanf("%d", &N);
    S = (int*)malloc((N) * sizeof(int));
    for (i = 0; i < N; ++i)
    {
        S[i] = -1;
    }
    while(true)
    {
        scanf("%c", &ENTER);
        scanf("%c", &op);
        if (op != 'S')
        {
            scanf(" %d %d", &a, &b);
            if (op == 'C')
            {
                Check(S, a-1, b-1);
            }
            else
            {
                Union(FindRoot(S, a-1), FindRoot(S, b-1));
            }
        }
        else
        {
            break;
        }
    }
    CheckAll(S, N);
    return 0;
}

void Check(int *S, int a, int b)
{
    if (FindRoot(S, a) == FindRoot(S, b))
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }
}

int FindRoot(int *S, int a)
{
    int i = a;
    while(S[i] >= 0)
    {
        i = S[i];
    }
    return i;
}

void Union(int *S, int a, int b)
{
    if (S[a] < S[b])
    {
        S[a] += S[b];
        S[b] = a;
    }
    else
    {
        S[b] += S[a];
        S[a] = b;
    }
}

void CheckAll(int *S, int N)
{
    int i, cnt = 0;
    for (i = 0; i < N; ++i)
    {
        if (S[i] < 0)
        {
            cnt++;
        }
    }
    if (cnt == 1)
    {
        printf("The network is connected.\n");
    }
    else
    {
        printf("There are %d components.\n", cnt);
    }
}