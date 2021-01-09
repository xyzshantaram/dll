#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

#define TYPE void*

struct Node {
    TYPE value;
    struct Node *next;
    struct Node *prev;
};

struct Node* append(struct Node* list, TYPE value);
/*
   Append the value to the list pointed to by list.
   If list is NULL, a new list will be created.
*/
struct Node* prepend(struct Node* list, TYPE value);
/*
   Prepend the value to the list pointed to by list.
   If list is NULL, a new list will be created.
*/
struct Node* populate_list(struct Node* list, int count, ...);
/*
    Appends "count" variadic arguments into the LL pointed to by 'list'.
    If list is NULL, returns a new list consisting of the given arguments.
    If append() fails due to malloc returning NULL, it destroys the
    constructed list and returns null. 
*/
struct Node* blank_list(struct Node* list, size_t count);
/*
    Appends "count" number of zeroes into the LL pointed to by 'list'.
    If list is NULL, returns a new list consisting of "count" number of zeroes.
    If append() fails due to malloc returning NULL, it destroys the
    constructed list and returns null. 
*/
void destroy_list(struct Node*);
/*
    Traverses the list and frees every Node in it.
*/
size_t length_of(struct Node* list);
/*
    Calculates and returns the length of the list. 0 if passed NULL.
*/
void put_at(struct Node*, size_t index, TYPE value);
/*
    Sets the value at the nth index of the list. If the index
    given is greater than the length of the list, sets errno
    to EINVAL and returns.
*/
TYPE value_at(struct Node* list, size_t index);
/*
    Gets the value at the nth index of the list. If the index
    given is greater than the length of the list, sets errno
    to EINVAL and returns zero.
*/
struct Node* get_nth_node(struct Node* list, size_t index);
/*
    Gets the nth node of the list. If the index given is greater than the
    length of the list, sets errno to EINVAL and returns NULL.
*/
struct Node* get_last_node(struct Node*);
/*
    Gets the last node of the given list.
*/
struct Node* get_first_node(struct Node*);
/*
    Gets the first node of the given list.
*/

void print(char *name, struct Node *list);
/*
    prints out a list.
*/
#define PRINT(x) print(#x, x)
/*
    Utility macro
*/
