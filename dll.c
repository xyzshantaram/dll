#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "dll.h"

struct DBLL_Node *dbll_append(struct DBLL_Node *list, DBLL_TYPE value) {
    list = dbll_get_last_node(list);

    struct DBLL_Node *new = malloc(sizeof(*new));
    if (!new) return NULL;

    new->next = NULL;
    new->value = value;

    if (list == NULL) {
        new->prev = NULL;
    }
    else {
        new->prev = list;
        list->next = new;
    }

    return new;
}

struct DBLL_Node *dbll_prepend(struct DBLL_Node *list, DBLL_TYPE value) {
    list = dbll_get_first_node(list);

    struct DBLL_Node *new = malloc(sizeof(*new));
    if (!new) return NULL;

    new->prev = NULL;
    new->value = value;

    if (list == NULL) {
        new->next = NULL;
    }
    else {
        new->next = list;
        list->prev = new;
    }

    return new;
}


size_t dbll_get_length(struct DBLL_Node *node) {
    node = dbll_get_first_node(node);
    size_t idx = 0;
    while (node) {
        idx++;
        if (!node->next) break;
        node = node->next;
    }
    return idx;
}

int dbll_insert_node(struct DBLL_Node *dest, DBLL_TYPE elem, int before) {
    if (!dest) {
        return 1;
    }

    struct DBLL_Node *new = malloc(sizeof(*new));
    if (!new) {
        return 2;
    }
    new->value = elem;
    if (!before) {
        new->next = dest->next;
        new->prev = dest;
        dest->next = new;
    }
    else {
        printf("inserting before\n");
        new->next = dest;
        new->prev = dest->prev;
        if (new->prev) new->prev->next = new;
        dest->prev = new;
    }
    return 0;
}

struct DBLL_Node *dbll_get_last_node(struct DBLL_Node *node) {
    while (node) {
        if (!node->next) break;
        node = node->next;
    }
    return node;
}

struct DBLL_Node *dbll_get_first_node(struct DBLL_Node *node) {
    while (node) {
        if (!node->prev) break;
        node = node->prev;
    }
    return node;
}

struct DBLL_Node *dbll_get_nth_node(struct DBLL_Node *node, size_t n) {
    node = dbll_get_first_node(node);
    for (int i = 0; i < n; i++) {
        if (!node) break;
        if (!node->next) break;
        node = node->next;
    }
    return node;
}

int dbll_put_at(struct DBLL_Node *node, size_t n, DBLL_TYPE value) {
    node = dbll_get_nth_node(node, n);
    if (!node) {
        return -1;
    }

    node->value = value;
    printf("%p %p\n", node, node->value);
    return 0;
}

DBLL_TYPE dbll_value_at(struct DBLL_Node *node, size_t n) {
    node = dbll_get_nth_node(node, n);
    if (!node) {
        errno = EINVAL;
        #if DBLL_VOID == 1
            return NULL;
        #else
            return -1;
        #endif
    }

    return node->value;
}

struct DBLL_Node *dbll_append_blanks(struct DBLL_Node *node, DBLL_TYPE value, size_t count) {
    struct DBLL_Node *first = node;
    struct DBLL_Node *tmp;
    printf("H\n");
    for (size_t i = 0; i < count; i++) {
        printf("H2\n");
        tmp = dbll_append(node, value);
        if (!tmp) {
            dbll_destroy_list(first);
            printf("F\n");
            return NULL;
        }
        else {
            node = tmp;
        }
    }
    if (!first) return tmp;
    else return first;
}

struct DBLL_Node *dbll_append_values(struct DBLL_Node *node, DBLL_TYPE values[], size_t count) {
    struct DBLL_Node *first = node;
    struct DBLL_Node *tmp;
    for (size_t i = 0; i < count; i++) {
        tmp = dbll_append(node, values[i]);
        if (!tmp) {
            dbll_destroy_list(first);
            return NULL;
        }
        else {
            node = tmp;
        }
    }
    if (!first) return tmp;
    else return first;
}

int dbll_find(struct DBLL_Node *list, DBLL_TYPE value) {

    while (list) {
        if (list->value == value) return 1;
        list = list->next;
    }
    return 0;
}

struct DBLL_Node *dbll_middle(struct DBLL_Node *list) {
    
    struct DBLL_Node *slow = list;
    struct DBLL_Node *fast = list->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct DBLL_Node *merge(struct DBLL_Node *a, struct DBLL_Node *b , int (*compare)(DBLL_TYPE, DBLL_TYPE)) {
    if (!a) return b;
    if (!b) return a;
    if (compare(a->value, b->value) <= 0) {
        a->next = merge(a->next, b, compare);
        a->next->prev = a;
        a->prev = NULL;
        return a;
    }
    else {
        b->next = merge(a, b->next, compare);
        b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}
struct DBLL_Node *dbll_sort(struct DBLL_Node *list, int (*compare)(DBLL_TYPE, DBLL_TYPE)) {
    if(!list || !list->next) return list;
    struct DBLL_Node *middle = dbll_middle(list);
    struct DBLL_Node *left = list;
    struct DBLL_Node *right = middle->next;
    middle->next = NULL;
    left = dbll_sort(left, compare);
    right = dbll_sort(right, compare);
    return merge(left, right, compare);
}

void dbll_print_list(const char *name, struct DBLL_Node *list) {
    list = dbll_get_first_node(list);
    printf("%s: ", name);
    for (struct DBLL_Node* itm = list; itm; itm = itm->next) {
        #if DBLL_VOID == 1
        printf("%p -> ", itm->value);
        #else
        printf("%d -> ", itm->value);
        #endif
    }
    printf("END\n");
}

void dbll_destroy_list(struct DBLL_Node *list) {
    list = dbll_get_first_node(list);
    struct DBLL_Node* next = list;
    while (next != NULL) {
        list = next;
        next = next->next;
        free(list);
    }
}

#if DBLL_VOID == 1
void dbll_destroy_list_freecontents(struct DBLL_Node *list) {
    list = dbll_get_first_node(list);
    struct DBLL_Node* next = list;
    while (next != NULL) {
        list = next;
        next = next->next;
        if (list->value) free(list->value);
        free(list);
    }
}
#endif
