#include <stdlib.h>

/*
    the type of the linked list. 
    DO NOT UPDATE THIS WITHOUT SETTING DBLL_VOID as follows:
    - 1 for void*
    - 0 for int
*/
#define DBLL_TYPE int

/*
    Controls access to type-specific functionality. 
    DO NOT UPDATE THIS WITHOUT SETTING DBLL_TYPE as follows:
    - void* for 1
    - int for 0
*/
#define DBLL_VOID 0

/* Helper macro to print a list and its name. */
#define DBLL_PRINT_LIST(x) dbll_print_list(#x, x);

/* 
    A list node.
*/
struct DBLL_Node {
    struct DBLL_Node *next;
    struct DBLL_Node *prev;
    DBLL_TYPE value;
};

#if DBLL_VOID == 1 // Function definitions specific to using the list in void* mode
/* 
    frees the contents of the list as it frees the list itself.
    ONLY USE THIS IF YOU ARE SURE THERE WILL ONLY BE VALUES IN THE LIST 
    ALLOCATED BY MALLOC / REALLOC.
    @param list the list to destroy
*/
void dbll_destroy_list_freecontents(struct DBLL_Node *list);
#endif

/* 
   Appends a value to a list given a reference to any node of the list. 
   If the pointer supplied is NULL, returns a new list with a single element.
   @param list a pointer to a list node, or NULL
   @param value a value to append to the list, either void* or int depending
   on the value of DBLL_TYPE
   @return the newly created node, and return NULL on malloc failure.
   Will not leak memory in this case.
*/
struct DBLL_Node *dbll_append(struct DBLL_Node *list, DBLL_TYPE value);

/* 
   Prepends a value to a list given a reference to any node of the list. 
   If the pointer supplied is NULL, returns a new list with a single element.
   @param list a pointer to a list node, or NULL
   @param value a value to insert at the starting of the list, either void* or int
   depending on the value of DBLL_TYPE.
   @return the newly created node, and NULL on malloc failure.
   Will not leak memory in this case.
*/
struct DBLL_Node *dbll_prepend(struct DBLL_Node *list, DBLL_TYPE value);

/*
    Gives the length of a list given any node in it.
    @return 0 if passed NULL, the length otherwise.
*/
size_t dbll_get_length(struct DBLL_Node *node);

/*
    Inserts an element into a list before or after the given node.
    @param dest the node to insert after/before
    @param elem the element to insert
    @param before a boolean specifying whether to insert before or after the given node
    @return 1 if NULL was passed in, 2 on malloc failure, 0 on success
*/
int dbll_insert_node(struct DBLL_Node *dest, DBLL_TYPE elem, int before);

/*
    Gets the last node of the list containing the given node.
    @return the last node of the list if a valid node pointer was passed in,
    NULL if NULL was passed in
    @param node any node of a list
    @return the last node of the list.
*/
struct DBLL_Node *dbll_get_last_node(struct DBLL_Node *node);

/*
    Gets the first node of the list containing the given node.
    @return the first node of the list if a valid node pointer was passed in,
    NULL if NULL was passed in
    @param node any node of a list
*/
struct DBLL_Node *dbll_get_first_node(struct DBLL_Node *node);

/*
    Gets the nth node of the list containing the given node.
    @param node any node in a given list
    @param an index
    @return the node at the specified index, NULL if the index doesn't exist or if the node passed in was NULL
*/
struct DBLL_Node *dbll_get_nth_node(struct DBLL_Node *node, size_t n);

/*
    Sets the value of an *existing* node in the list to the given value. 
    @return 0 on success, -1 on failure
*/
int dbll_put_at(struct DBLL_Node *node, size_t n, DBLL_TYPE value);

/*
    Gets the value of the list node at the given index. 
    Sets errno to EINVAL on failure.
    @param any node of a list
    @return (void*|int). NULL or -1 if the node at the given index wasn't found, or the value of the node otherwise.
*/
DBLL_TYPE dbll_value_at(struct DBLL_Node *node, size_t n);

/*
    Appends n items to the list, each with value specified by `value`. 
    Will create a new list if NULL is passed in. 
    If memory allocation fails, destroys the created list to avoid leaking memory.
    @param node any node in the list
    @param value the value of each new element
    @param count the number of new elements to create
    @return the original node if a valid pointer was passed in, a new list if NULL was passed in, and NULL on allocation failure
*/
struct DBLL_Node *dbll_append_blanks(struct DBLL_Node *node, DBLL_TYPE value, size_t count);

/*
    Appends n items to the list from an array. 
    Will create a new list if NULL is passed in. 
    If memory allocation fails, destroys the created list to avoid leaking memory. 
    IT'S THE CALLER'S RESPONSIBILITY TO MAKE SURE THERE ARE ENOUGH VALUES IN THE ARRAY!
    @param any node in the list
    @param values an array containing the elements to append
    @param count the number of new elements to create
    @return the original node if a valid pointer was passed in, a new list if NULL was passed in, and NULL on allocation failure
*/

int dbll_find(struct DBLL_Node *list, DBLL_TYPE value);

/*
    Searches if a node is present .
    @param list a pointer to a list node
    @param value the value to search for
    @return 1 if the node is present in list, or the value of the node otherwise.
*/

struct DBLL_Node *dbll_middle(struct DBLL_Node *list);

/*
    Finds the middle node of a list.
    @param list a pointer to a list node
    @return the middle node of the list, or NULL if the list is empty.

*/

struct DBLL_Node *dbll_sort(struct DBLL_Node *list, int (*compare)(DBLL_TYPE, DBLL_TYPE));

/*
    Sorts the list.
    @param list a pointer to a list node
    @param compare a function pointer to a function that compares two values
    @return the sorted list
*/

struct DBLL_Node *dbll_append_values(struct DBLL_Node *node, DBLL_TYPE values[], size_t count);

/*
    Prints out the list in this format.
    elem1 -> elem2 -> elem3 -> END
*/
void dbll_print_list(const char *name, struct DBLL_Node *list);

/*
    Traverses the list and frees all the pointers in it.
*/
void dbll_destroy_list(struct DBLL_Node *list);
