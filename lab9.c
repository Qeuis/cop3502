#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 50

struct RecordType
{
    int id;
    char name[NAME_SIZE];
    int order;
    struct RecordType *next;
};

struct HashType
{
    struct RecordType *head;
};

int hash(int x, int tableSize)
{
    const int prime = 31;  
    return ((x * prime) % tableSize);
}


int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char name[NAME_SIZE];
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%s ", name);
            strncpy(pRecord->name, name, NAME_SIZE);
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}


void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %s %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}


void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);
    struct RecordType *temp = hashTable[index].head;
    struct RecordType *prev = NULL;

    while (temp != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
    {
        hashTable[index].head = record;
    }
    else
    {
        prev->next = record;
    }
}

void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    printf("\nRecords in the hash table:\n");
    for (int i = 0; i < tableSize; ++i)
    {
        struct RecordType *temp = hashTable[i].head;
        printf("Index %d: ", i);

        // Sort the linked list in ascending order of the order field
        struct RecordType *sortedList = NULL;
        while (temp != NULL)
        {
            struct RecordType *next = temp->next;
            if (sortedList == NULL || temp->order < sortedList->order)
            {
                temp->next = sortedList;
                sortedList = temp;
            }
            else
            {
                struct RecordType *current = sortedList;
                while (current->next != NULL && temp->order >= current->next->order)
                {
                    current = current->next;
                }
                temp->next = current->next;
                current->next = temp;
            }
            temp = next;
        }

        // Traverse the sorted linked list and print out the records
        temp = sortedList;
        while (temp != NULL)
        {
            printf("%d %s %d -> ", temp->id, temp->name, temp->order);
            temp = temp->next;
        }
        printf("\n");

        // Free the memory used by the sorted linked list
        temp = sortedList;
        while (temp != NULL)
        {
            struct RecordType *next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main(void)
{
    struct RecordType *data;
    int dataSz, tableSize;

    printf("Enter the size of the hash table: ");
    scanf("%d", &tableSize);

    dataSz = parseData("input.txt", &data);

    struct HashType *hashTable = (struct HashType *)malloc(sizeof(struct HashType) * tableSize);
    for (int i = 0; i < tableSize; ++i)
    {
        hashTable[i].head = NULL;
    }

    for (int i = 0; i < dataSz; ++i)
    {
        insertRecord(hashTable, &data[i], tableSize);
    }

    printRecords(data, dataSz);
    displayRecordsInHash(hashTable, tableSize);

    free(hashTable);
    free(data);

    return 0;
}