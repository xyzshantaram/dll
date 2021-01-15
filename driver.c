#include "dll.h"

int main() {
    errno = 0;

    struct DBLL_Node* list = append(NULL, 0);
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
