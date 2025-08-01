#include "map.h"

void print_string(void *data)
{
    printf("%s", (char *)data);
}

void print_int(void *data)
{
    printf("%d", *(int *)data);
}

void print_char(void *data)
{
    printf("%c", *(char *)data);
}

void print_float(void *data)
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

Proccess_responses new_response(Repsone_codes code, Data_type type_of_value)
{
    Proccess_responses res;
    res.code = code;
    snprintf(res.return_message, MAX_STRING_BUFFER, "%s", GET_MESSAGE_CODE[code]);
    return res;
}

Node_return new_node(void *key, void *value, Data_type type_of_key, Data_type type_of_value)
{
    Node_return res;

    Node *node = malloc(sizeof(Node));

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
    map.curr_size = INITIAL_SIZE;
    map.type_of_key = type_of_key;
    map.type_of_value = type_of_value;

    map.methods.are_equal = GET_ARE_EQUAL_FUNC[type_of_key];
    map.methods.print_key = GET_PRINT_FUNC[type_of_key];
    map.methods.print_value = GET_PRINT_FUNC[type_of_value];

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
        // return new_response();
    }

    if ((map->type_of_key == STRING) && (strlen((char *)key) + 1 > MAX_STRING_BUFFER))
    {
        // return new_response()
    }

    if ((map->type_of_value == STRING) && (strlen((char *)value) + 1 > MAX_STRING_BUFFER))
    {
        // return new_response()
    }

    // unsigned int
}

// int hash()
// {

// }
