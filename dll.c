#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>


struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
};

struct Node* append(struct Node* list, int value);
/*
   Append the value to the list pointed to by list.
   If list is NULL, a new list will be created.
*/
struct Node* prepend(struct Node* list, int value);
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
struct Node* blank_list(struct Node* list, int count);
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
void put_at(struct Node*, size_t index, int value);
/*
    Sets the value at the nth index of the list. If the index
    given is greater than the length of the list, sets errno
    to EINVAL and returns.
*/
int  value_at(struct Node* list, size_t index);
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
struct Node* append(struct Node *list, int value) {
    struct Node* first = list;
    list = get_last_node(list);

    struct Node* new = malloc(sizeof(struct Node));
    if (new == NULL) {
    	return NULL;
    }

    new->next = NULL;
    new->prev = NULL;
    new->value = value;

    if (list == NULL) {
    	return new;
    }

    else {
        new->prev = list;
    	list->next = new;
    }
    return first;
}

struct Node* prepend(struct Node* list, int value) {
    list = get_first_node(list);
    struct Node *new;
    if (list == NULL) {
        new = append(NULL, 0);
    }
    else {
        new = malloc(sizeof(*new));
        if (new == NULL) {
            return NULL;
        }
        list->prev = new;
        new->next = list;
        new->value = value;
        new->prev = NULL;
    }

    return new;
}

struct Node *populate_list(struct Node* list, int count, ...) {
    va_list ap;
    va_start(ap, count);

    struct Node* first;
    for (int i = 0; i < count; i++) {
        int value = va_arg(ap, int);
        list = append(list, value);
        if (list == NULL) {
            destroy_list(first);
            return NULL;
        }
        if (i == 0) {
            first = list;
        }
    }

    return first;
}

struct Node *blank_list(struct Node* list, int count) {
    struct Node* first = list;
    for (int i = 0; i < count; i++) {
        list = append(list, 0);
        if (list == NULL) {
            destroy_list(first);
            return NULL;
        }
        if (i == 0) {
            first = list;
        }
    }
    return first;
}

void destroy_list(struct Node *list) {
    list = get_first_node(list);
    struct Node* next = list;
    while(next != NULL) {
        list = next;
        next = next->next;
        free(list);
    }
}

size_t length_of(struct Node *list) {
    list = get_first_node(list);
	size_t count = 0;
	while (list != NULL) {
		list = list->next;
		count++;
	}
	return count;
}
void put_at(struct Node* list, size_t index, int value) {
    struct Node* node = get_nth_node(list, index);
    if (node == NULL) return; // Don't forget to check errno!
    else node->value = value;
}

int value_at(struct Node* list, size_t index) {
    struct Node* node = get_nth_node(list, index);
    if (node == NULL) return -1; // Don't forget to check errno!
    else return node->value;
}

struct Node* get_nth_node(struct Node* list, size_t index) {
    list = get_first_node(list);
    if (list == NULL) {
        return NULL;
    }

    if (index > length_of(list) - 1) {
        errno = EINVAL;
        return NULL;
    }

    for (int i = 0; i < index; i++) {
        list = list->next;
    }
    return list;
}

struct Node* get_last_node(struct Node* list) {
    return get_nth_node(list, length_of(list) - 1);
}

struct Node* get_first_node(struct Node* list) {
    if (list) {
        while(list->prev != NULL) {
            list = list->prev;
        }
        return list;
    }
    return NULL;
}

void print(char *name, struct Node *list) {
	printf("%s: ", name);
	while (list != NULL) {
		printf("%d -> ", list->value);
		list = list->next;
	}
	printf("NULL\n");
}

int main() {
    errno = 0;

    struct Node* list = append(NULL, 0);
    list = append(list, 1);
    list = prepend(list, 2);
    populate_list(list, 3, 1, 2, 3);
    struct Node* list2 = blank_list(NULL, 3);
    printf("Lengths of created lists are %zu and %zu.\n", length_of(list), length_of(list2));
    put_at(list2, 2, 69);
    printf("%d\n", get_first_node(get_last_node(list2))->next->next->value);
    if (errno != 0) {
    	perror("put_at");
    	exit(1);
    }
    int val = value_at(list2, 2);
    if (val == -1 && errno != 0) {
    	perror("value_at");
    	exit(1);
    }
    printf("Value at index 2: %d\n", val);

    if (list == NULL) {
        printf("malloc failed while building list, exiting...\n");
        return 1;
    }

    PRINT(list);
    PRINT(list2);

    destroy_list(list);
    destroy_list(list2);
    return 0;
}
