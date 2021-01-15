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
dbll_append() returns NULL in case of an allocation failure and the original pointer it was passed otherwise. If NULL was passed in,
it will return a new list node.
```c
    list = dbll_append(list, 1);
```
#### Prepend a value to the list
Returns a pointer to the newly prepended node, ie the new first node of the list.
```c
    list = prepend(list, 2);
```
#### Populate a list with values
If NULL is passed as the first argument, it returns a new list with the given values. The second argument is the number of values to append.
```c
    populate_list(list, 3, 1, 2, 3);
```
#### Get a list filled with zeroes
If you pass in a valid Node pointer, it appends the specified number of zeroes to the end of that list.
```c
    struct Node* list2 = blank_list(NULL, 3);
```
#### Get the length of a list
Returns zero if NULL is passed in.
```c
    printf("Length of created list is %d\n", length_of(list));
```
#### Set the value stored in a node
Set the value stored in the node at the given (absolute, zero-indexed) index to the given value. If the index does not exist in the list, errno is set to EINVAL.
```c
    put_at(list2, 2, 69);
```
#### Get the last node of a list
Returns NULL if NULL is passed in.
```c
    struct Node* last = get_last_node(list);
```
#### Get the first node of a list
Returns NULL if NULL is passed in.
```c
    struct Node* first = get_first_node(list);
```
#### Get the nth value of a list
Returns 0 and sets errno to EINVAL if the nth index does not exist.
```c
    int val = value_at(list, 2);
```
#### Get the nth node of a list
Returns a NULL pointer and sets errno to EINVAL if the nth index does not exist.
```c
    struct Node* nth = get_nth_node(list, 2);
```
#### Pretty-print the list
Prints out the list with its name in the following format:    
"listname: node0 -> node1 -> node2 ... nodeN -> NULL"
```c
    PRINT(list);
```
#### Destroy the list
Frees every node in the list.
```c
    destroy_list(list);
```
Provided under the MIT License, (C) 2020 Siddharth Singh
