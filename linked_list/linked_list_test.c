#include "linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sll_print(sll_node* head) {
    sll_node* current = head;
    sll_node* next    = current;

    while (current != NULL) {
        printf("{");
        // printf("%zu, ", sll_get_priority(current));
        printf("%s, ", (char*)sll_get_data(current));

        printf("%p", sll_get_next(current));

        printf("} -> \n");
        current = sll_get_next(current);
    }
    printf("NULL\n");
    return;
}

bool comparison_func(sll_node* node, size_t argc, void* args[]) {

    char* data_string = (char*)sll_get_data(node);
    char* arg         = (char*)args[0];

    if (strcmp(data_string, arg)) {
        int i = strcmp(data_string, arg);
        return false;
    }

    return true;
}

int main() {
    char*     data = "hello";
    sll_node* head = sll_create_node(data);

    int i = 1;

    while (i <= 10) {
        char* data = "node";
        // char* new_data = NULL;
        // char  new_data[100];
        char* new_data = (char*)malloc(10);
        sprintf(new_data, "%s %d", data, i);
        sll_append(new_data, head);
        i++;
    }

    sll_print(head);

    // delete 8
    void* args[10];
    args[0] = "node 8";
    sll_delete_node(head, comparison_func, 1, args);
    sll_print(head);

    // reinsert 8
    char* reinsert8 = (char*)malloc(10);
    reinsert8       = "node 8";
    args[0]         = "node 7";
    sll_insert_after(reinsert8, head, comparison_func, 1, args);
    sll_print(head);

    // delete 1
    sll_delete_first(head);
    sll_print(head);

    // re-insert 1
    char* reinsert1 = (char*)malloc(10);
    reinsert1       = "node 1";
    sll_insert_first(reinsert1, head);
    sll_print(head);

    // append 11
    char* append_data = (char*)malloc(10);
    append_data       = "node 11";
    sll_append(append_data, head);
    sll_print(head);

    return 0;
}
