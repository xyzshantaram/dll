#include <stdio.h>
#include <errno.h>

#include "dll.h"

int compare(int a,int b){
    return b-a;
}
int main() {
    errno = 0;
    struct DBLL_Node* list = dbll_append(NULL, 0);
    if (list == NULL) {
        printf("malloc failed while building list, exiting...\n");
        return 1;
    }
    list = dbll_append(list, 1);
    list = dbll_prepend(list, 2);
    int values[] = {1,2,3};
    dbll_append_values(list, values, 3);
    struct DBLL_Node* list2 = dbll_append_blanks(NULL, 0, 3);
    printf("Lengths of created lists are %zu and %zu.\n", dbll_get_length(list), dbll_get_length(list2));
    dbll_put_at(list2, 2, 69);
    printf("%d\n", dbll_get_first_node(dbll_get_last_node(list2))->next->next->value);
    if (errno != 0) {
    	perror("put_at");
    	exit(1);
    }
    int val = dbll_value_at(list2, 2);
    if (val == -1 && errno != 0) {
    	perror("value_at");
    	exit(1);
    }
    printf("Value at index 2: %d\n", val);

    DBLL_PRINT_LIST(list);
    DBLL_PRINT_LIST(list2);
    printf("Searching for 100(prints 1 if found) :%d\n",dbll_find(list, 100));
    printf("Searching for 2(prints 1 if found) :%d\n",dbll_find(list, 2));
    int values1[] = {9,7,8,6,5,0,1};
    dbll_append_values(list, values1, 7);
    list = dbll_sort(list,compare);
    DBLL_PRINT_LIST(list);
    dbll_destroy_list(list2);

    return 0;
}
