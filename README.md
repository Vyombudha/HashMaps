# HashMap in C
This repository implements a hash map in C with separate chaining using linked lists for collision resolution. It stores key-value string pairs (max 256 characters) in a table of 1234 buckets, built on a custom linked list. This version improves on an earlier HashMap with better structure and error handling, designed for personal learning.
Features

Stores null-terminated string keys and values (≤256 characters).
Operations:
newMap: Creates a hash map with 1234 buckets.
insert: Adds a key-value pair.
search: Returns the value for a key or NULL if not found.
deleteValue: Removes a key-value pair by key.
printTable: Prints non-empty buckets.
freeTable: Frees all memory.


DJB2-based hash function for key indexing.
Error handling for memory allocation failures and string overflows.
Collisions handled via linked lists.

Installation

Clone the repo:
git clone https://github.com/your-username/HashMaps.git
cd HashMaps


Compile:
gcc -o hash_map hash_map.c list.c


Run:
./hash_map



Note: Add a main function to hash_map.c or use the example below.
Usage
#include "hash_map.h"

int main() {
    hashMap *map = newMap();
    insert(&map, "name", "Vyom Budha");
    insert(&map, "age", "17");
    printTable(map);
    char *value = search(map, "name");
    printf("Key 'name': %s\n", value ? value : "Not found");
    freeTable(&map);
    return 0;
}

Output:
Index: <hash>, Pairs: name: Vyom Budha, age: 17
Key 'name': Vyom Budha

Error Handling

Checks memory allocation for map, table, and nodes.
Validates string lengths (<256 characters) to prevent overflows.
Reports missing keys or empty lists with messages.

Project Structure

hash_map.h, hash_map.c: HashMap implementation.
list.h, list.c: Linked list for chaining.
README.md: This documentation.
