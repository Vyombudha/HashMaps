#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

#define MAXSIZE 1234

typedef struct hashMap
{
    struct linkedList **table;
} hashMap;

hashMap *newMap()
{
    // HashMap Struct allocation
    hashMap *map = malloc(sizeof(struct hashMap));
    if (map == NULL)
    {
        printf("Error In Allocating Memory for HashMap!\n");
        exit(EXIT_FAILURE);
    }

    // HashTable initialization
    struct linkedList **table = malloc(sizeof(struct linkedList *) * MAXSIZE);
    if (table == NULL)
    {
        printf("Error In Allocating Memory for HashTable of MAXSIZE %d\n", MAXSIZE);
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < MAXSIZE; i++)
        {
            table[i] = createList();
        }
    }
    map->table = table;
    return map;
}

int hash(char key[])
{
    unsigned long hash1 = 5381;
    int c;
    while ((c = *key++))
        hash1 *= 33 + c; // hash * 33 + c
    return hash1 % MAXSIZE;
}

char *search(hashMap *map, char key[])
{
    struct linkedList **table = map->table;
    int index = hash(key);
    return searchInList(table[index], key); // returns value if found and then NOT_FOUND if not found
}

void insert(hashMap **map, char key[], char value[])
{
    int index = hash(key);
    struct linkedList **table = (*map)->table; // Make a pointer to 'tales' linked List array
    insertToList(&table[index], key, value);   // Auto hanldes Collision Cases and insertions
}

void printTable(struct hashMap *map)
{
    struct linkedList **table = map->table;
    for (int i = 0; i < MAXSIZE; i++)
    {
        if(table[i]->head == NULL) // an empty list will be skipped
        {
            continue;
        }
        printList(table[i], i); 
        printf("\n");
    }
}

void freeTable(struct hashMap **map)
{
    struct linkedList **table = (*map)->table;
    for (int i = 0; i < MAXSIZE; i++)
    {
        freeList(&table[i]); // free each linkedList aka bucket one by one 
    }
    free(table); // free the pointer to the array of linkedList itself
    free(*map);
}

void deleteValue(struct hashMap **map, char key[])
{
    struct linkedList **table = (*map)->table;
    int index = hash(key); // get the index for this key
    char *result = search(*map, key); 
    if (result != NULL) // if the key exits in the table
    {
        deleteNodeByKey(&table[index], key); // delete this key's node
        printf("Node of key: %s is in %d index of the Table and has been deleted!\n", key, index);
    }
    else
    {
        printf("Key: %s is not in the given table!, Try again\n", key); // else tell it doesn't exist in the table
    }
}

// int main()
// {
//     hashMap *map1 = newMap();

//     insert(&map1, "name", "vyom budha");
//     insert(&map1, "age", "17");
//     insert(&map1, "address", "imadol");

//     printf("The hash table is:\n");
//     printTable(map1);

//     char key[] = "name";
//     char* value = search(map1,key);
//     printf("The Value for the key %s is %s",key,value);


//     freeTable(&map1);
//     return 0;
// }