#include "dll_vp.h"

struct Node* append(struct Node *list, TYPE value) {
    struct Node* first = list;
    list = get_last_node(list);

    struct Node* new = malloc(sizeof(struct Node));
    if (new == NULL) {
    	return NULL;
    }

    if (list == NULL) {
    	return new;
    }

    else {
        if (!list->value && list->prev && !list->next) {
            free(new);
            list->value = value;
        }
        else {
            new->prev = list;
    	    list->next = new;
        }
    }
    return first;
}

struct Node* prepend(struct Node* list, TYPE value) {
    list = get_first_node(list);
    struct Node *new;
    if (list == NULL) {
        new = append(NULL, NULL);
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
        TYPE value = va_arg(ap, TYPE);
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

struct Node *blank_list(struct Node* list, size_t count) {
    struct Node* first = list;
    for (size_t i = 0; i < count; i++) {
        list = append(list, NULL);
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
        if (list->value) free(list->value);
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
void put_at(struct Node* list, size_t index, TYPE value) {
    struct Node* node = get_nth_node(list, index);
    if (node == NULL) return; // Don't forget to check errno!
    else node->value = value;
}

TYPE value_at(struct Node* list, size_t index) {
    struct Node* node = get_nth_node(list, index);
    if (node == NULL) return NULL; // Don't forget to check errno!
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

    for (size_t i = 0; i < index; i++) {
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
		printf("%p -> ", list->value);
		list = list->next;
	}
	printf("NULL\n");
}


