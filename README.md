# HashMaps


1. Prototype-1:
-> This my Codebase that implements hash maps in C. It uses the linkedList implementation that I had previsouly made last week as buckets       for the seperate chainging in each Index of the table. 
 
 Usage Guide
Create a New Hash Map:
hashMap *map1 = newMap();
Creates a new hash map with MAX_SIZE number of indexes.

Insert a (key, value) Pair:
insert(&map1, key, value);


key and value are null-terminated strings with a maximum buffer size of 256 characters (including '\0').


Print the Entire Map:
printMap(map1);


Search for a Value by Key:
char* result = search(map1, key);
Returns a pointer to the value associated with the given key. Returns NULL if the key is not found.


Free the Hash Map:
freeTable(&map1);
Frees all linked lists in the table and deallocates the hash map itself.


Notes:
Collisions are handled with separate chaining using linked lists.
Ensure key and value strings are properly null-terminated and within the 256-character buffer limit.
