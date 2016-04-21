/*
* Data Structures in C
* Find the path in heap.
* LuoYingYing
* 20160421
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxData -10001

typedef int ElementType;
typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MinHeap CreateHeap(int MaxSize);
void Insert2Heap(MinHeap H, ElementType elem);
void FindPath(MinHeap H, int index);
bool IsFull(MinHeap H);

int main(int argc, char const *argv[])
{
    int M, N, i, index;
    ElementType elem;
    MinHeap H;
    scanf("%d %d", &M, &N);
    H = CreateHeap(M);
    for (i = 0; i < M; ++i)
    {
        scanf("%d", &elem);
        Insert2Heap(H, elem);
    }
    for (i = 0; i < N; ++i)
    {
        scanf("%d", &index);
        FindPath(H, index);
    }
    return 0;
}

MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType*)malloc((MaxSize+1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;
    return H;
}

void Insert2Heap(MinHeap H, ElementType elem)
{
    if (IsFull(H))
    {
        printf("The Heap is full.\n");
    }
    else
    {
        int i;
        i = ++ H->Size;
        while(H->Elements[i/2] > elem)
        {
            H->Elements[i] = H->Elements[i/2];
            i /= 2;
        }
        H->Elements[i] = elem;
    }
}


bool IsFull(MinHeap H)
{
    return H->Size == H->Capacity;
}

void FindPath(MinHeap H, int index)
{
    bool isFirstPrint = true;
    while( index )
    {
        if (isFirstPrint)
        {
            isFirstPrint = false;
        }
        else
        {
            printf(" ");
        }
        printf("%d", H->Elements[index]);
        index /= 2;
    }
    printf("\n");
}