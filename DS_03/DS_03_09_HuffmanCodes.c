/*
* Data Structures in C
* Huffman Codes.
* LuoYingYing
* 20160428
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct HuffmanTree *HT;
typedef struct HeapStruct *MinHeap;
typedef HT ElementType;
struct HeapStruct
{
    ElementType *Elements;
    int Size;
    int Capacity;
};

struct HuffmanTree
{
    int Weight;
    HT Left;
    HT Right;
};

void FreeHT(HT T);
void Judge(HT T, int *Weights, int N1, int N2);
void ReadData(MinHeap H, int *Weights, int N);
void Codes2Tree(HT *T, char op);
int WPL(HT T, int Depth);
HT Huffman(MinHeap H);
MinHeap CreateHeap(int MaxSize);
ElementType DeleteMin(MinHeap H);
void Insert2Heap(MinHeap H, ElementType elem);
bool IsEmpty(MinHeap H);
bool IsFull(MinHeap H);


int main(int argc, char const *argv[])
{
    int N1, N2, i;
    int *Weights;
    MinHeap H;
    scanf("%d", &N1);
    Weights = (int*)malloc(N1 * sizeof(int));
    H = CreateHeap(N1);
    ReadData(H, Weights, N1);
    HT T = Huffman(H);
    scanf("%d", &N2);
    char Enter;
    scanf("%c", &Enter);
    Judge(T, Weights, N1, N2);
    return 0;
}


void ReadData(MinHeap H, int *Weights, int N)
{
    int i, weight;
    char Enter;
    HT temp;
    for (i = 0; i < N; ++i)
    {
        scanf("%c%c %d", &Enter, &Enter, &weight);
        temp = (HT)malloc(sizeof(struct HuffmanTree));
        temp->Weight = Weights[i] = weight;
        temp->Left = temp->Right = NULL;
        Insert2Heap(H, temp);
    }
}

void Judge(HT T, int *Weights, int N1, int N2)
{
    char *str;
    int i, j, k;
    int codeLen = WPL(T, 0);
    int sumLen;
    bool isOK;
    HT JudgeT, tempT;
    for (i = 0; i < N2; ++i)
    {
        sumLen = 0;
        isOK = true;
        JudgeT = (HT)malloc(sizeof(struct HuffmanTree));
        JudgeT->Left = JudgeT->Right = NULL;
        for (j = 0; j < N1; ++j)
        {
            int cnt = 0;
            str = (char*)malloc((N1 + 2) * sizeof(char));
            gets(str);
            while (str[cnt] != '\0')
            {
                cnt++;
            }
            if (cnt > N1 + 1)
            {
                isOK = false;
            }
            if (isOK)
            {
                tempT = JudgeT;
                sumLen += (cnt - 2)*Weights[j];
                for (k = 2; k < cnt - 1; ++k)
                {
                    Codes2Tree(&tempT, str[k]);
                }
                if ((!tempT->Left && str[k] == '0') || (!tempT->Right && str[k] == '1'))
                {
                    Codes2Tree(&tempT, str[k]);
                }
                else
                {
                    isOK = false;
                }
            }
        }
        FreeHT(JudgeT);
        if (codeLen != sumLen)
        {
            isOK = false;
        }
        if (isOK)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}

void FreeHT(HT T)
{
    if (T != NULL)
    {
        FreeHT(T->Left);
        FreeHT(T->Right);
        free(T);
    }
}

void Codes2Tree(HT *T, char op)
{
    if (op == '0')
    {
        if ((*T)->Left == NULL)
        {
            (*T)->Left = (HT)malloc(sizeof(struct HuffmanTree));
            (*T)->Left->Left = (*T)->Left->Right = NULL;
        }
        *T = (*T)->Left;
    }
    else
    {
        if ((*T)->Right == NULL)
        {
            (*T)->Right = (HT)malloc(sizeof(struct HuffmanTree));
            (*T)->Right->Left = (*T)->Right->Right = NULL;
        }
        *T = (*T)->Right;
    }
}

int WPL(HT T, int Depth)
{
    if (!T->Left && !T->Right)
    {
        return Depth * T->Weight;
    }
    else
    {
        return WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1);
    }
}

HT Huffman(MinHeap H)
{
    int i;
    HT temp;
    int cnt = H->Size;
    for (i = 0; i < cnt-1; ++i)
    {
        temp = (HT)malloc(sizeof(struct HuffmanTree));
        temp->Left = DeleteMin(H);
        temp->Right = DeleteMin(H);
        temp->Weight = temp->Left->Weight + temp->Right->Weight;
        Insert2Heap(H, temp);
    }
    return DeleteMin(H);
}

MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->Elements = (HT*)malloc((MaxSize + 1) * sizeof(HT));
    ElementType MinData = (ElementType)malloc(sizeof(struct HuffmanTree));
    MinData->Weight = 0;

    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MinData;
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
        i = ++H->Size;
        while (H->Elements[i / 2]->Weight > elem->Weight)
        {
            H->Elements[i] = H->Elements[i / 2];
            i /= 2;
        }
        H->Elements[i] = elem;
    }
}

ElementType DeleteMin(MinHeap H)
{
    if (IsEmpty(H))
    {
        printf("The Heap is empty.\n");
        return NULL;
    }
    else
    {
        ElementType minElem = H->Elements[1];
        ElementType temp = H->Elements[H->Size--];
        int i = 1;
        while (((2*i <= H->Size) && (H->Elements[2 * i]->Weight < temp->Weight)) || ((2*i + 1 <= H->Size) && (H->Elements[2 * i + 1]->Weight < temp->Weight)))
        {
            if (H->Elements[2 * i]->Weight < H->Elements[2 * i + 1]->Weight)
            {
                H->Elements[i] = H->Elements[2 * i];
                i *= 2;
            }
            else
            {
                H->Elements[i] = H->Elements[2 * i + 1];
                i = i * 2 + 1;
            }
        }
        H->Elements[i] = temp;
        return minElem;
    }
}

bool IsEmpty(MinHeap H)
{
    return H->Size == 0;
}

bool IsFull(MinHeap H)
{
    return H->Size == H->Capacity;
}
