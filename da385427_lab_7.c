#include <stdio.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    int numSwaps[n];
    for (i = 0; i < n; i++)
    {
        numSwaps[i] = 0;
    } 

    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
                numSwaps[j]++;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        printf("Number of swaps needed for index %d: %d\n", i, numSwaps[i]);
    }
}

int main()
{
    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    bubbleSort(arr, 9);
    return 0;
}