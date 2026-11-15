#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define NO_VALUE_CHAR '\0'
#define NO_VALUE_INT -99099
#define NO_VALUE_FLOAT -99099.0f
#define NO_VALUE_STRING "NO_VALUE_STRING"

#define MAX_STRING_BUFFER 257
#define INITIAL_SIZE 1024

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
    MAP_PRINTING_SUCCESSFUL = 7,
    MAP_LINKED_LIST_ALLOCATION_ERROR = 8,
    MAP_NODE_ALLOCATION_ERROR = 9,
    MAP_REHASHING_SUCCESSFUL = 10,
    MAP_LINKED_LIST_NULL_POINTER = 11,
    OK = 12,
    MAP_KEY_NOT_FOUND = 13,
} Repsone_codes;

// Define ALL structs first before any function declarations
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
    void (*assign_value)(Returning_value *, void *);
} data_methods;

typedef struct
{
    Node **linked_lists;
    Data_type type_of_value;
    Data_type type_of_key;
    data_methods methods;
    unsigned int (*hash)(const void *, size_t);
    size_t max_size;
    size_t curr_size;
} Map;

// NOW declare external variables and functions (after struct definitions)
extern const char *GET_MESSAGE_CODE[14];
extern const size_t GET_SIZE_OF[4];
extern void (*GET_PRINT_FUNC[4])(const void *);
extern bool (*GET_ARE_EQUAL_FUNC[4])(const void *, const void *);
extern unsigned int (*GET_HASH_FUNC[4])(const void *, size_t);
extern void (*GET_ASSIGN_VALUE_FUNC[4])(Returning_value *, void *);

// Function declarations
void print_string(const void *data);
void print_int(const void *data);
void print_char(const void *data);
void print_float(const void *data);

bool are_equal_int(const void *key_to_search, const void *key_in_map);
bool are_equal_string(const void *key_to_search, const void *key_in_map);
bool are_equal_char(const void *key_to_search, const void *key_in_map);
bool are_equal_float(const void *key_to_search, const void *key_in_map);

unsigned int hash_string(const void *key, size_t max_size);
unsigned int hash_int_or_char(const void *key, size_t max_size);
unsigned int hash_float(const void *key, size_t max_size);

void assign_value_int(Returning_value *value, void *data);
void assign_value_char(Returning_value *value, void *data);
void assign_value_string(Returning_value *value, void *data);
void assign_value_float(Returning_value *value, void *data);

Proccess_responses new_response(Repsone_codes code);
Node_return new_node(void *key, void *value, Data_type type_of_key, Data_type type_of_value);
Proccess_responses insert_node_to_list(Node **head, Node *node);
Map new_map(Data_type type_of_key, Data_type type_of_value);
Proccess_responses map_set(Map *map, void *key, void *value);
Proccess_responses map_value(const Map *map, void *key);
bool map_has(const Map *map, void *key);
Proccess_responses map_print(const Map *map);
Proccess_responses map_destroy(Map *map);
Proccess_responses map_rehash(Map *map);

#endif
