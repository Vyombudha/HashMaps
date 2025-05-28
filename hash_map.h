#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"


#define MAXSIZE 1234

typedef struct hashMap
{
    struct linkedList **table; // it consists of the array of pointers to linkedLists
} hashMap;


hashMap *newMap();


// functions that work by pass by reference i.e passing the address of the original value : fucntion_name(&map)
void insert(hashMap **map, char key[], char value[]);
void deleteValue(struct hashMap **map, char key[]);
void freeTable(struct hashMap **map);


// functions that work by pass by value i.e passing the original value itself : function_name(map)
int hash(char key[]);
char *search(hashMap *map, char key[]);
void printTable(struct hashMap *map);



#endif
