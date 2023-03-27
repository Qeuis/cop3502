#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// merge two subarrays of pData[]
// helper function

void merge(int pData[], int l, int m, int r) 
{
	int i, j, k;
	int temp1 = m - l + 1;
	int temp2 = r - m;

	// allocate memory for temporary arrays

	int* left = (int*) malloc(temp1 * sizeof(int));
	int* right = (int*) malloc(temp2 * sizeof(int));
	extraMemoryAllocated += (temp1 + temp2) * sizeof(int);

	// copy data into temporary arrays
	for (i = 0; i < temp1; i++)
	{
		left[i] = pData[l + 1];
	}

	for (j = 0; j < temp2; j++)
	{
		right[i] = pData[m + 1 + j];
	}

	// merge the temporary arrays back into pData[]
	i = 0; // initial index of first subarray
	j = 0; // initial index of second subarray
	k = l; // inital index of merged subarray

	while(i < temp1 && j < temp2)
	{
		if(left[i] <= right[j])
		{
			pData[k] = left[j];
			i++;
			// increment index of first subarray if less than second subarray
		}
		else
		{
			pData[k] = right[j];
			j++;
			// increment index of second subarray if less than first subarray
		}
		k++; // increment index of merged subarray
	}

	// copy any remaining elements of left[]
	while (i < temp1)
	{
		pData[k] = left[i];
		i++;
		k++;
	}

	// copy any remain elemnts of right[]
	while (j < temp2)
	{
		pData[k] = right[j];
		j++;
		k++;
	}

	// free temporary arrays
	free(left);
	free(right);
	extraMemoryAllocated -= (temp1  + temp2) * sizeof(int);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int m  = l + (r - 1) / 2; // find the mid point
		mergeSort(pData, l, m); // sort first half of the array
		mergeSort(pData, m + 1, r); // sort the second half of the array
		merge(pData, l, m, r); // merge the sorted halves

		extraMemoryAllocated += sizeof(int) * (r - l + 1);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, key;
	for (i = 1; i < n; i ++)
	{
		key = pData[i];
		j = i - 1;

		while (j >= 0 && pData[j] > key)
		{
			pData[j + 1] = pData[j];
			j--;
		}
		pData[j + 1] = key;
	}

	extraMemoryAllocated += sizeof(int) * n;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	extraMemoryAllocated = 0;
	int i, j, temp;
	for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-1; j++)
		{
			if (pData[j] > pData[j+1])
			{
			 temp = pData[i];
			 pData[j] = pData[j+1];
			 pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	extraMemoryAllocated = 0;
	int i, j, temp, minIndex;
	for(i = 0; i < n-1; i++)
	{
		minIndex = i;
		for (j = i + 1; j < n; j++)
		{
			if (pData[j] < pData[minIndex])
			{
				minIndex = j;
			}
		}

		temp = pData[i];
		pData[i] = pData[minIndex];
		pData[minIndex] = temp;
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		// read integers from file and store in an array
		for (int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", &(*ppData)[i]);
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}