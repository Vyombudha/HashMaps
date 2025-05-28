#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* The Node will be each index of the LinkedList consisting of Node which Stores key and value pair of size 256 characters and then
   the pointer to the next Node */

typedef struct Node
{
    char key[256], value[256];
    struct Node *next;
} Node;

/* The linkedList is the struct where we will keep track of head and tail nodes to make Passing a specific List into functions more easy
   and insertions very efficient at O(1) aka Constant Time */

typedef struct linkedList
{
    Node *head;
    Node *tail;
} linkedList;

/* These are the Create Node Functions */
Node *createNode(char key[], char value[]);
struct linkedList *createList();

/* These are the List Modifying/Printing Functions */
void insertToList(struct linkedList **list, char key[], char value[]);
void printList(struct linkedList *list, int index);
void freeList(struct linkedList **list);
char *searchInList(struct linkedList *list, char key[]);
void deleteNodeByValue(struct linkedList **list, char value[]);
void deleteNodeByKey(struct linkedList **list, char key[]);

#endif // LIST_H