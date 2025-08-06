#include "map.h"

const char *GET_MESSAGE_CODE[14] = {
    [MAP_NULL_POINTER] = "Map pointer is NULL",
    [MAP_SET_SUCCESSFUL] = "Map set successful",
    [MAP_GET_SUCCESSFUL] = "Map get successful",
    [MAP_VALUE_ALLOCATION_FALIURE] = "Value allocation failure",
    [MAP_KEY_ALLOCATION_FALIURE] = "Key allocation failure",
    [MAP_VALUE_NULL_POINTER] = "Value pointer is NULL",
    [MAP_KEY_NULL_POINTER] = "Key pointer is NULL",
    [MAP_PRINTING_SUCCESSFUL] = "Map printing successful",
    [MAP_LINKED_LIST_ALLOCATION_ERROR] = "Linked list allocation error",
    [MAP_NODE_ALLOCATION_ERROR] = "Node allocation error",
    [MAP_REHASHING_SUCCESSFUL] = "Rehashing successful",
    [MAP_LINKED_LIST_NULL_POINTER] = "Linked list pointer is NULL",
    [OK] = "Operation successful",
    [MAP_KEY_NOT_FOUND] = "Key not found in map"};

const size_t GET_SIZE_OF[4] = {
    [STRING] = MAX_STRING_BUFFER,
    [INT] = sizeof(int),
    [CHAR] = sizeof(char),
    [FLOAT] = sizeof(float)};

void (*GET_PRINT_FUNC[4])(const void *) = {
    [STRING] = print_string,
    [INT] = print_int,
    [CHAR] = print_char,
    [FLOAT] = print_float};

bool (*GET_ARE_EQUAL_FUNC[4])(const void *, const void *) = {
    [STRING] = are_equal_string,
    [INT] = are_equal_int,
    [CHAR] = are_equal_char,
    [FLOAT] = are_equal_float};

unsigned int (*GET_HASH_FUNC[4])(const void *, size_t) = {
    [STRING] = hash_string,
    [INT] = hash_int_or_char,
    [CHAR] = hash_int_or_char,
    [FLOAT] = hash_float};

void (*GET_ASSIGN_VALUE_FUNC[4])(Returning_value *, void *) = {
    [STRING] = assign_value_string,
    [INT] = assign_value_int,
    [CHAR] = assign_value_char,
    [FLOAT] = assign_value_float};

void print_string(const void *data)
{
    printf("%s", (char *)data);
}

void print_int(const void *data)
{
    printf("%d", *(int *)data);
}

void print_char(const void *data)
{
    printf("%c", *(char *)data);
}

void print_float(const void *data)
{
    printf("%f", *(float *)data);
}

bool are_equal_int(const void *key_to_search, const void *key_in_map)
{
    return *(int *)key_in_map == *(int *)key_to_search;
}

bool are_equal_string(const void *key_to_search, const void *key_in_map)
{
    return strcmp((char *)key_in_map, (char *)key_to_search) == 0;
}

bool are_equal_char(const void *key_to_search, const void *key_in_map)
{
    return *(char *)key_in_map == *(char *)key_to_search;
}

bool are_equal_float(const void *key_to_search, const void *key_in_map)
{
    return *(float *)key_in_map == *(float *)key_to_search;
}
// Hash functions for different data types
// These functions take a key and the maximum size of the map to ensure the hash fits within the bounds of the linked list array.
// For strings, a simple hash function is used, while for integers and characters, a modulo operation is applied.
// For floats, the float is treated as an unsigned int for hashing purposes.
unsigned int hash_string(const void *key, size_t max_size)
{
    const char *str = (const char *)key;
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % max_size; // Ensure the hash fits within the bounds of the linked list array
}
unsigned int hash_int_or_char(const void *key, size_t max_size)
{
    return *(int *)key % max_size; // Simple hash for integers, can be improved
}

unsigned int hash_float(const void *key, size_t max_size)
{
    unsigned int hash = *(unsigned int *)key; // Treat float as an unsigned int for hashing
    return hash % max_size;                   // Ensure the hash fits within the bounds of the linked list array
}

void assign_value_int(Returning_value *value, void *data)
{
    (*value).integer = *(int *)data;
}

void assign_value_char(Returning_value *value, void *data)
{
    (*value).character = *(char *)data;
}

void assign_value_string(Returning_value *value, void *data)
{
    snprintf((*value).string, MAX_STRING_BUFFER, "%s", (char *)data);
}

void assign_value_float(Returning_value *value, void *data)
{
    (*value).floating_number = *(float *)data;
}

Proccess_responses new_response(Repsone_codes code)
{
    Proccess_responses res;
    res.code = code;
    snprintf(res.return_message, MAX_STRING_BUFFER, "%s", GET_MESSAGE_CODE[code]);

    // Initialize the Returning_value with default values
    res.value.integer = NO_VALUE_INT;
    res.value.floating_number = NO_VALUE_FLOAT;
    res.value.character = NO_VALUE_CHAR;
    snprintf(res.value.string, MAX_STRING_BUFFER, "%s", NO_VALUE_STRING);

    return res;
}

Node_return new_node(void *key, void *value, Data_type type_of_key, Data_type type_of_value)
{
    Node_return res;

    Node *node = malloc(sizeof(Node));

    if (key == NULL)
    {
        res.code = MAP_KEY_NULL_POINTER;
        res.returning_node = NULL;
        return res;
    }

    if (value == NULL)
    {
        res.code = MAP_VALUE_NULL_POINTER;
        res.returning_node = NULL;
        return res;
    }

    if (node == NULL)
    {
        res.code = MAP_NODE_ALLOCATION_ERROR;
        res.returning_node = NULL;
        return res;
    }

    node->key = malloc(GET_SIZE_OF[type_of_key]);
    if (node->key == NULL)
    {
        free(node); // clean up node itself
        res.code = MAP_KEY_ALLOCATION_FALIURE;
        res.returning_node = NULL;
        return res;
    }

    node->value = malloc(GET_SIZE_OF[type_of_value]);
    if (node->value == NULL)
    {
        free(node->key); //  clean up already allocated key
        free(node);
        res.code = MAP_VALUE_ALLOCATION_FALIURE;
        res.returning_node = NULL;
        return res;
    }

    memcpy(node->key, key, GET_SIZE_OF[type_of_key]);
    memcpy(node->value, value, GET_SIZE_OF[type_of_value]);

    res.returning_node = node;
    res.code = OK;

    return res;
}

Map new_map(Data_type type_of_key, Data_type type_of_value)
{
    Map map;
    map.max_size = INITIAL_SIZE;
    map.curr_size = 0;
    map.type_of_key = type_of_key;
    map.type_of_value = type_of_value;

    map.methods.are_equal = GET_ARE_EQUAL_FUNC[type_of_key];
    map.methods.print_key = GET_PRINT_FUNC[type_of_key];

    map.methods.print_value = GET_PRINT_FUNC[type_of_value];
    map.methods.assign_value = GET_ASSIGN_VALUE_FUNC[type_of_value];

    map.hash = GET_HASH_FUNC[type_of_key];

    map.linked_lists = malloc(sizeof(Node *) * map.max_size);
    if (map.linked_lists == NULL)
    {
        printf("ERROR!, CRITCAL FALIUREL: %s. new_map() UNSUCCESSFUL!\n", GET_MESSAGE_CODE[MAP_LINKED_LIST_ALLOCATION_ERROR]); // this is a critical faliure!, So we will print the Error and return map immediately!!
        return map;
    }

    for (int i = 0; i < map.max_size; i++)
    {
        map.linked_lists[i] = NULL; // setting all head Nodes to NULL!
    }

    return map;
}
Proccess_responses map_set(Map *map, void *key, void *value)
{

    if (map == NULL)
    {
        return new_response(MAP_NULL_POINTER);
    }

    if ((map->type_of_key == STRING) && (strlen((char *)key) + 1 > MAX_STRING_BUFFER))
    {
        return new_response(MAP_KEY_ALLOCATION_FALIURE);
    }

    if ((map->type_of_value == STRING) && (strlen((char *)value) + 1 > MAX_STRING_BUFFER))
    {
        return new_response(MAP_VALUE_ALLOCATION_FALIURE);
    }

    if (map->linked_lists == NULL)
    {
        return new_response(MAP_LINKED_LIST_NULL_POINTER);
    }

    // Check if Map is 70% full and needs rehashing
    if (map->curr_size >= 0.7 * map->max_size)
    {
        Proccess_responses res = map_rehash(map);
        if (res.code != MAP_REHASHING_SUCCESSFUL)
        {
            return res; // If rehashing fails, return the error
        }
    }

    unsigned int index = map->hash(key, map->max_size);

    // Making a new Node with the key and value
    Node_return node_res = new_node(key, value, map->type_of_key, map->type_of_value);

    if (node_res.code != OK)
    {
        return new_response(node_res.code);
    }

    // If the node was created successfully, we will insert it into the linked list at the index
    Proccess_responses res = insert_node_to_list(&map->linked_lists[index], node_res.returning_node);

    if (res.code == OK)
    {
        res.code = MAP_SET_SUCCESSFUL;
        map->curr_size++;
    }

    return res;
}

Proccess_responses map_value(const Map *map, void *key)
{
    if (map == NULL)
    {
        return new_response(MAP_NULL_POINTER);
    }

    if (map->linked_lists == NULL)
    {
        return new_response(MAP_LINKED_LIST_NULL_POINTER);
    }

    if (key == NULL)
    {
        return new_response(MAP_KEY_NULL_POINTER);
    }

    unsigned int index = map->hash(key, map->max_size);

    Node *current = map->linked_lists[index];

    while (current != NULL)
    {
        if (map->methods.are_equal(key, current->key))
        {
            Proccess_responses res = new_response(MAP_GET_SUCCESSFUL);
            map->methods.assign_value(&res.value, current->value);
            return res;
        }
        current = current->next;
    }
    // If we reach here, the key was not found
    return new_response(MAP_KEY_NOT_FOUND);
}

Proccess_responses insert_node_to_list(Node **head, Node *node)
{
    // To access the original head pointer, you must dereference it (*head).
    if (*head == NULL)
    {
        *head = node; // This now modifies the original pointer.
    }
    else
    {
        node->next = *head; // The new node points to the old head.
        *head = node;       // The original head pointer is updated to the new node.
    }

    return new_response(OK);
}

Proccess_responses map_destroy(Map *map)
{

    if (map == NULL)
    {
        return new_response(MAP_NULL_POINTER);
    }

    if (map->linked_lists == NULL)
    {
        return new_response(MAP_LINKED_LIST_NULL_POINTER);
    }

    for (size_t i = 0; i < map->max_size; i++)
    {
        Node *current = map->linked_lists[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(map->linked_lists);
    map->linked_lists = NULL;
    map->curr_size = 0;
    return new_response(OK);
}

Proccess_responses map_rehash(Map *map)
{
    if (map == NULL)
    {
        return new_response(MAP_NULL_POINTER);
    }

    size_t old_size = map->max_size;
    Node **old_linked_lists = map->linked_lists;

    map->max_size *= 2; // Double the size
    map->curr_size = 0; // Reset current size

    map->linked_lists = malloc(sizeof(Node *) * map->max_size);

    if (map->linked_lists == NULL)
    {
        // Critical failure, restore old state
        map->linked_lists = old_linked_lists;
        map->max_size = old_size;
        return new_response(MAP_LINKED_LIST_ALLOCATION_ERROR);
    }

    for (size_t i = 0; i < map->max_size; i++)
    {
        map->linked_lists[i] = NULL; // Initialize new linked lists
    }

    // Rehash all existing nodes from the old table
    for (size_t i = 0; i < old_size; i++)
    {
        Node *current = old_linked_lists[i]; // Get the head of the old chain
        while (current != NULL)              // Iterate through the ENTIRE chain
        {
            // Re-insert the key-value pair into the new, larger map
            Proccess_responses res = map_set(map, current->key, current->value);
            if (res.code != MAP_SET_SUCCESSFUL)
            {
                return res;
            }

            Node *temp = current;    // Save current node to be freed
            current = current->next; // Move to the next node in the old chain

            // Free the old node and its data
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    // After processing all old nodes, free the old table itself.
    free(old_linked_lists);

    return new_response(MAP_REHASHING_SUCCESSFUL);
}

bool map_has(const Map *map, void *key)
{
    if (map == NULL || map->linked_lists == NULL || key == NULL)
    {
        return false; // Map is NULL, cannot have any keys
    }

    unsigned int index = map->hash(key, map->max_size);

    Node *current = map->linked_lists[index];

    while (current != NULL)
    {
        if (map->methods.are_equal(key, current->key))
        {
            return true; // Key found
        }
        current = current->next;
    }

    return false; // Key not found
}

Proccess_responses map_print(const Map *map)
{
    if (map == NULL)
    {
        return new_response(MAP_NULL_POINTER);
    }

    if (map->linked_lists == NULL)
    {
        return new_response(MAP_LINKED_LIST_NULL_POINTER);
    }

    for (size_t i = 0; i < map->max_size; i++)
    {
        Node *current = map->linked_lists[i];
        if (current == NULL)
        {
            continue; // Skip empty linked lists
        }

        printf("Index %u:\n", i);
        while (current != NULL)
        {
            map->methods.print_key(current->key);
            printf(" : ");
            map->methods.print_value(current->value);
            current = current->next;
            printf("\n");
        }

        printf("\n");
    }

    return new_response(MAP_PRINTING_SUCCESSFUL);
}
