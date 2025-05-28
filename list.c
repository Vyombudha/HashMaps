#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    char key[256], value[256];
    struct Node *next;
} Node;

typedef struct linkedList
{
    Node *head;
    Node *tail;
}linkedList;

Node *createNode(char key[], char value[])
{
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("\n\nError in allocating Memory for node with key %s and Value %s\n\n", key, value);
        exit(EXIT_FAILURE);
    }
    if (strlen(key) < 256 && strlen(value) < 256)
    {
        strcpy(newNode->key, key);
        strcpy(newNode->value, value);
        newNode->next = NULL;
    }
    else
    {
        printf("\n\nSTRING OVERLOAD ERROR!, SIZE FOR THE key : %s or Value: %s, EXCEEDS THE PREDEFINED 256 characters INCLUDING NULL TERMINATOR, Try With New Shorter Strings!\n\n", key, value);
        exit(EXIT_FAILURE);
    }
    return newNode;
}

void insertToList(struct linkedList **list, char key[], char value[])
{
    struct Node *node = createNode(key, value);

    if (node == NULL)
    {
        printf("\n\nError in memory allocation for Node!\n\n");
        exit(EXIT_FAILURE);
    }

    if ((*list)->head == NULL)
    {
        (*list)->head = node;
        (*list)->tail = node;
    }
    else
    {
        (*list)->tail->next = node;
        (*list)->tail = node;
    }
}

void printList(struct linkedList *list, int index)
{
    struct Node *temp = list->head;
    if (temp == NULL)
    {
        printf("Index: %d, <empty>: <empty>", index);
        return;
    }

    if (temp == list->tail)
    {
        printf("Index: %d,  %s: %s", index, temp->key, temp->value);
        return;
    }

    printf("Index: %d, Pairs: ", index);
    while (temp != NULL)
    {
        if (temp == list->tail)
        {
            printf("%s: %s", temp->key, temp->value);
        }
        else
        {
            printf("%s: %s, ", temp->key, temp->value);
        }
        temp = temp->next;
    }
}

struct linkedList *createList()
{
    struct linkedList *list = malloc(sizeof(struct linkedList));
    if (list == NULL)
    {
        printf("\n\nError in memory allocation for Linked List!\n\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void freeList(struct linkedList **list)
{
    struct Node *temp = (*list)->head, *currentNode;
    while (temp != NULL)
    {
        currentNode = temp;
        temp = temp->next;
        free(currentNode);
    }
    free(*list);
    *list = NULL;
}

char *searchInList(struct linkedList *list, char key[])
{
    struct Node *temp = list->head;
    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0)
        {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

void deleteNodeByValue(struct linkedList **list, char value[])
{
    struct Node *temp = (*list)->head, *prev = NULL;

    if (temp == NULL) // if List is empty
    {
        printf("\nThe List is empty!\nTry again with a non empty List\n");
        return;
    }

    if (strcmp(temp->value, value) == 0) //  if head node is the node to be deleted
    {
        if ((*list)->tail == (*list)->head) //  if it is single Node List
        {
            free(temp);
            (*list)->tail = NULL;
            (*list)->head = NULL;
        }
        else
        {
            (*list)->head = (*list)->head->next;
            free(temp);
        }
        return;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->value, value) == 0)
        {
            printf("\n\nValue: %s was found in the List and has benn deleted!\n\n", value);
            if (temp == (*list)->tail)
            {
                prev->next = NULL;
                (*list)->tail = prev;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("\n\nValue: %s was not found in the List!\n\n", value);
}

void deleteNodeByKey(struct linkedList **list, char key[])
{
    struct Node *temp = (*list)->head, *prev = NULL;

    if (temp == NULL) // if List is empty
    {
        printf("\n\nThe List is empty!\nTry again with a non empty List\n\n");
        return;
    }

    if (strcmp(temp->key, key) == 0) //  if head node is the node to be deleted
    {
        if ((*list)->tail == (*list)->head) //  if it is single Node List
        {
            (*list)->tail = NULL;
            (*list)->head = NULL;
        }
        else
        {
            (*list)->head = (*list)->head->next;
        }
        free(temp);
        return;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0)
        {
            printf("\n\nkey: %s was found in the List and has benn deleted!\n\n", key);
            if (temp == (*list)->tail)
            {
                prev->next = NULL;
                (*list)->tail = prev;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("\n\nkey: %s was not found in the List!\n\n", key);
}
