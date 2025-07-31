Map.h is a design for a new Template Based LinkedList I am working in at the moment! , In Day 1, I was able to get some thing working but map_value() which should retrun value for a specific key but, I haven't figured which method would be best to hanlde this!, I am working towards a union!, but let's see!, 

something like a 


typedef union{
int num;
char* str;
char chl
init flt;
}return_values;

typedef struct{
... // same as in map.h
return_values value;
}Procsesse_response;
