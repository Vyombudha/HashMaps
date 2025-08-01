#ifndef MAP_H
#define MAP_H

// Map myMap<INT,STRING> = Map<>() ;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

const char NO_VALUE = '\0';
const size_t MAX_STRING_BUFFER = 257;
const size_t INITIAL_SIZE = 157;

typedef enum
{
    STRING,
    INT,
    CHAR,
    FLOAT
} Data_type;

typedef enum
{
    MAP_SET_SUCCESSFUL = 0,
    MAP_GET_SUCCESSFUL = 1,
    MAP_VALUE_ALLOCATION_FALIURE = 2,
    MAP_KEY_ALLOCATION_FALIURE = 3,
    MAP_VALUE_NULL_POINTER = 4,
    MAP_KEY_NULL_POINTER = 5,
    MAP_NULL_POINTER = 6,
    MAP_FULL = 7,
    MAP_PRINTING_SUCCESSFUL = 8,
    MAP_LINKED_LIST_ALLOCATION_ERROR = 9,
    MAP_NODE_ALLOCATION_ERROR = 10,
    OK = 11
} Repsone_codes;

const char *GET_MESSAGE_CODE[12] = {
    [MAP_SET_SUCCESSFUL] = "MAP_SET_SUCCESSFUL",
    [MAP_GET_SUCCESSFUL] = "MAP_GET_SUCCESSFUL",
    [MAP_VALUE_ALLOCATION_FALIURE] = "MAP_VALUE_ALLOCATION_FALIURE",
    [MAP_KEY_ALLOCATION_FALIURE] = "MAP_KEY_ALLOCATION_FALIURE",
    [MAP_VALUE_NULL_POINTER] = "MAP_VALUE_NULL_POINTER",
    [MAP_KEY_NULL_POINTER] = "MAP_KEY_NULL_POINTER",
    [MAP_NULL_POINTER] = "MAP_NULL_POINTER",
    [MAP_FULL] = "MAP_FULL",
    [MAP_PRINTING_SUCCESSFUL] = "MAP_PRINTING_SUCCESSFUL",
    [MAP_LINKED_LIST_ALLOCATION_ERROR] = "MAP_LINKED_LIST_ALLOCATION_ERROR",
    [MAP_NODE_ALLOCATION_ERROR] = "MAP_NODE_ALLOCATION_ERROR",
    [OK] = "OK"};

const size_t GET_SIZE_OF[4] = {
    [STRING] = MAX_STRING_BUFFER,
    [INT] = sizeof(int),
    [CHAR] = sizeof(char),
    [FLOAT] = sizeof(float)};

void print_string(void *data);
void print_int(void *data);
void print_char(void *data);
void print_float(void *data);

// Array of function Pointer!!
void (*GET_PRINT_FUNC[4])(void *) = {
    [STRING] = print_string,
    [INT] = print_int,
    [CHAR] = print_char,
    [FLOAT] = print_float};

bool are_equal_int(const void *key_to_search, const void *key_in_map);
bool are_equal_string(const void *key_to_search, const void *key_in_map);
bool are_equal_char(const void *key_to_search, const void *key_in_map);
bool are_equal_float(const void *key_to_search, const void *key_in_map);

bool (*GET_ARE_EQUAL_FUNC[4])(const void *, const void *) = {
    [STRING] = are_equal_string,
    [INT] = are_equal_int,
    [CHAR] = are_equal_char,
    [FLOAT] = are_equal_float};

// This is the definition of Proccess_repsonse Struct and it's newResponse()  and !

typedef struct
{
    int integer;
    float floating_number;
    char character;
    char string[MAX_STRING_BUFFER];
} Returning_value;

typedef struct
{
    Repsone_codes code;
    char return_message[MAX_STRING_BUFFER];
    Returning_value value;
} Proccess_responses;

Proccess_responses new_response(Repsone_codes code, Data_type type_of_value); // will auto generate

// These are the Functions/ Definitions handling Nodes/Map
// This should return the Data_type Approprite value when map_value_of() is called under Proccess_response

typedef struct Node
{
    void *key;
    void *value;
    struct Node *next;
} Node;

typedef struct
{
    Node *returning_node;
    Repsone_codes code;
} Node_return;

typedef struct
{
    bool (*are_equal)(const void *, const void *);
    void (*print_key)(const void *);
    void (*print_value)(const void *);
} data_methods;

typedef struct
{
    Node **linked_lists; //  this is a pointer to a pointer pointing to an Array of Linked_list Nodes; || the Insert function for the Nodes will be Head inserted!
    Data_type type_of_value;
    Data_type type_of_key;

    data_methods methods;

    size_t max_size;
    size_t curr_size;
} Map;

Node_return new_node(void *key, void *value, Data_type type_of_key, Data_type type_of_value);

// Map myMap  = new_map(INT,STRING,19) ;

Map new_map(Data_type type_of_key, Data_type type_of_value);

Proccess_responses map_set(Map *map, void *key, void *value);
Proccess_responses map_value(const Map *map, void *key); // I MAY HAVE SOME WAY TO RETURN AN APPROPIRATE RETURN VALUE!!
bool map_has(const Map *map, void *key);

Proccess_responses map_print(const Map *map); // will internally call linked_list[index]->print_key()(and)->print_value(); in a LOOP
Proccess_responses map_destroy(Map *map);     // will internally  free all linked_list[index] Nodes and set linked_lists to NULL!
Proccess_responses map_rehash(Map *map);      // Will Be used to reHash the map!

#endif
