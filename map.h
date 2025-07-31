#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAP_SIZE 1537
#define MAX_STRING_BUFFER 267

typedef enum
{
    STRING,
    INT,
    CHAR,
    FLOAT
} Data_type;

// Not a dataType to  Size Mapper, But I will most likely make it a function Pointer mapper!!
// it will be needed to change or something, and probaly defined at the end of all the function signatures are defined!
// repsonses will be a error handling object for something!
// const repsonses(*GET_SIZE[4])() = {

// };

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
    MAP_LINKED_LIST_ALLOCATION_ERROR = 9
} Repsone_codes;

void print_string(void *data);
void print_int(void *data);
void print_char(void *data);
void print_float(void *data);

void (*GET_PRINT_FUNC[4])(void *) = {
    [STRING] = print_string,
    [INT] = print_int,
    [CHAR] = print_char,
    [FLOAT] = print_float};

// This is the definition of Proccess_repsonse Struct and it's newResponse()  and !
typedef struct
{
    Repsone_codes code;
    char return_message[MAX_STRING_BUFFER];
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
    Node **linked_lists; //  this could be a pointer to a pointer pointing to an Array of Linked_list Nodes but I decied not todo that!

    Data_type type_of_key;
    Data_type type_of_value;
    void (*print_key)(void *); // ApproPriate print_(Data_type) function will be assigned to these two when a new Map is created!
    void (*print_value)(void *);
} Map;

Node new_node(void *data, Data_type type_of_data);

Map new_map(Data_type type_of_key, Data_type type_of_value);
Proccess_responses map_set(Map *map, void *key, void *value);
Proccess_responses map_value_of(const Map *map, void *key); // IDK, How to find an Appropriate Solution to this!!, I have on idea how to make this Actually working without making it type unsafe!
bool map_has(const Map *map, void *key);

Proccess_responses map_print(const Map *map); // will internally call linked_list[index]->print_key()(and)->print_value(); in a LOOP
Proccess_responses map_destroy(Map *map);     // will internally  free all linked_list[index] Nodes and set linked_lists to NULL!

#endif
