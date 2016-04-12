/*
* Data Structures in C
* Binary Search
* 20160319
* LuoYingYing
*/

#include <stdio.h>

int BinarySearch(int List[], int N, int X);
int BinarySearchByRecursiveImpl(int List[], int left, int right, int X);
int BinarySearchByIterativeImpl(int List[], int left, int right, int X);

int main(int argc, char const *argv[])
{
    int List[5] = {1, 2, 5, 7, 9};
    int X = 9;
    printf("%d\n", BinarySearch(List, 5, X));
    return 0;
}

int BinarySearch(int List[], int N, int X)
{
    //return BinarySearchByRecursiveImpl(List, 0, N-1, X);
    return BinarySearchByIterativeImpl(List, 0, N-1, X);
}

/* RecursiveImpl */
int BinarySearchByRecursiveImpl(int List[], int left, int right, int X)
{
    if (left > right)
    {
        return -1;//The num -1 means not found
    }
    int center = (left + right)/2;
    if ( List[center] == X )
    {
        return center;
    }
    else if ( List[center] < X )
    {
        return BinarySearchByRecursiveImpl(List, center+1, right, X);
    }
    else
    {
        return BinarySearchByRecursiveImpl(List, left, center-1, X);
    }
}

/* IterativeImpl */
int BinarySearchByIterativeImpl(int List[], int left, int right, int X)
{
    int center;
    int result = -1;//The num -1 means not found
    while (left <= right && result == -1)
    {
        center = (left + right)/2;
        if ( List[center] == X )
        {
            result = center;
        }
        else if ( List[center] < X )
        {
            left = center+1;
        }
        else
        {
            right = center-1;
        }
    }
    return result;
}