# dll
C implementation of a doubly-linked list datatype.

## Usage:

#### Add to your program
```c
#include "dll.h"
```
Make sure to edit dll.h to set the values of DBLL_TYPE and DBLL_VOID as per your usage (void* vs int)    
To use it as a linked list of void*s, set the following values:
```c
    #define DBLL_TYPE void*
    #define DBLL_VOID 1
```
For a linked list of ints, set:
```c
    #define DBLL_TYPE int
    #define DBLL_VOID 0
```
#### Create a new list
The dbll_append() call pulls double duty for appending and creating new lists.
```c
    struct DBLL_Node* list = dbll_append(NULL, 0);
```
#### Append a value to a list
dbll_append() returns NULL in case of an allocation failure and the original pointer it was passed otherwise. If NULL was passed in, it will return a new list node.
```c
    list = dbll_append(list, 1);
```
#### Prepend a value to the list
Returns a pointer to the newly prepended node, ie the new first node of the list, or NULL on allocation failure.
```c
    list = dbll_prepend(list, 2);
```
#### Populate a list with values from an array
If NULL is passed as the first argument, it returns a new list with the given values. The second argument is the number of values to append.
MAKE SURE THERE ARE ATLEAST AS MANY VALUES IN THE ARRAY AS YOU INTEND TO APPEND!
```c
    int arr[] = {1, 2, 3, 4};
    dbll_append_values(list, arr, 3);
```
#### Get a list filled with a certain value
If a valid DBLL_Node pointer is passed in, it appends the specified count of the specified value to the end of that list, and returns a new list if NULL is passed in.
```c
    struct DBLL_Node* list2 = dbll_append_blanks(NULL, 0, 3);
    // Creates a new list with 3 elements, each with value 0.
```
#### Get the length of a list
Returns zero if NULL is passed in.
```c
    printf("Length of created list is %d\n", dbll_get_length(list));
```
#### Set the value stored in a node
Set the value stored in the node at the given (absolute, zero-indexed) index to the given value. If the index does not exist in the list, returns -1. Returns 0 on success.
```c
    dbll_put_at(list2, 2, 69); // sets the third element of list2 to 69
```
#### Insert a node before or after a given node
dbll_insert_node() will return 2 on malloc failure, 1 if null was passed in, 0 on success.
```
    int before = 0; // a boolean specifying whether to insert before or after the given element
    int elem = 55; // the element to insert
    int r = dbll_insert_node(list, elem, before);
```
#### Get the last node of a list
Returns NULL if NULL is passed in.
```c
    struct DBLL_Node* last = dbll_get_last_node(list);
```
#### Get the first node of a list
Returns NULL if NULL is passed in.
```c
    struct DBLL_Node* first = dbll_get_first_node(list);
```
#### Get the nth value of a list
If the nth index does not exist, sets errno to EINVAL _and_:
    * Returns _-1_ **in int mode**
    * Returns _NULL_ **in void* mode**
```c
    int val = dbll_value_at(list, 2);
```
#### Get the nth node of a list
Returns a NULL pointer and sets errno to EINVAL if the nth index does not exist.
```c
    struct DBLL_Node* nth = dbll_get_nth_node(list, 2);
```
#### Pretty-print the list
Prints out the list with its name in the following format:    
"listname: node0value -> node1value -> node2value ... nodeNvalue -> END"
```c
    DBLL_PRINT_LIST(list);
```
#### Destroy the list
Frees every node in the list.
```c
    dbll_destroy_list(list);
```

##### Notes
- Please don't use this library to create circular linked lists, or any kind of list involving cycles - all the functions would just break down, since they assume a linear structure.

Provided under the MIT License, (C) 2020 Siddharth Singh
